


#include "IxEthDB_p.h"
#include "IxEthDBLocks_p.h"


void ixEthDBInitHash(HashTable *hashTable, 
                     UINT32 numBuckets, 
                     HashFunction entryHashFunction, 
                     MatchFunction *matchFunctions, 
                     FreeFunction freeFunction)
{
    UINT32 bucketIndex;
    UINT32 hashSize = numBuckets * sizeof(HashNode *);

    /* entry hashing, matching and freeing methods */
    hashTable->entryHashFunction  = entryHashFunction;
    hashTable->matchFunctions     = matchFunctions;
    hashTable->freeFunction       = freeFunction;

    /* buckets */
    hashTable->numBuckets = numBuckets;

    /* set to 0 all buckets */
    memset(hashTable->hashBuckets, 0, hashSize);

    /* init bucket locks - note that initially all mutexes are unlocked after MutexInit()*/
    for (bucketIndex = 0 ; bucketIndex < numBuckets ; bucketIndex++)
    {
        ixOsalFastMutexInit(&hashTable->bucketLocks[bucketIndex]);
    }
}

IX_ETH_DB_PUBLIC IxEthDBStatus ixEthDBAddHashEntry(HashTable *hashTable, void *entry)
{
    UINT32 hashValue   = hashTable->entryHashFunction(entry);
    UINT32 bucketIndex = hashValue % hashTable->numBuckets;
    HashNode *bucket   = hashTable->hashBuckets[bucketIndex];
    HashNode *newNode;

    LockStack locks;

    INIT_STACK(&locks);

    /* lock bucket */
    PUSH_LOCK(&locks, &hashTable->bucketLocks[bucketIndex]);

    /* lock insertion element (first in chain), if any */
    if (bucket != NULL)
    {
        PUSH_LOCK(&locks, &bucket->lock);
    }

    /* get new node */
    newNode = ixEthDBAllocHashNode();

    if (newNode == NULL)
    {
        /* unlock everything */
        UNROLL_STACK(&locks);

        return IX_ETH_DB_NOMEM;
    }

    /* init lock - note that mutexes are unlocked after MutexInit */
    ixOsalFastMutexInit(&newNode->lock);

    /* populate new link */
    newNode->data = entry;

    /* add to bucket */
    newNode->next                       = bucket;
    hashTable->hashBuckets[bucketIndex] = newNode;

    /* unlock bucket and insertion point */
    UNROLL_STACK(&locks);

    return IX_ETH_DB_SUCCESS;
}

IxEthDBStatus ixEthDBRemoveHashEntry(HashTable *hashTable, int keyType, void *reference)
{
    UINT32 hashValue       = hashTable->entryHashFunction(reference);
    UINT32 bucketIndex     = hashValue % hashTable->numBuckets;
    HashNode *node         = hashTable->hashBuckets[bucketIndex];
    HashNode *previousNode = NULL;
    
    LockStack locks;

    INIT_STACK(&locks);

    while (node != NULL)
    {
        /* try to lock node */
        PUSH_LOCK(&locks, &node->lock);

        if (hashTable->matchFunctions[keyType](reference, node->data))
        {
            /* found entry */
            if (node->next != NULL)
            {
                PUSH_LOCK(&locks, &node->next->lock);
            }

            if (previousNode == NULL)
            {
                /* node is head of chain */
                PUSH_LOCK(&locks, &hashTable->bucketLocks[bucketIndex]);

                hashTable->hashBuckets[bucketIndex] = node->next;

                POP_LOCK(&locks);
            }
            else
            {
                /* relink */
                previousNode->next = node->next;
            }

            UNROLL_STACK(&locks);

            /* free node */
            hashTable->freeFunction(node->data);
            ixEthDBFreeHashNode(node);

            return IX_ETH_DB_SUCCESS;
        }
        else
        {
            if (previousNode != NULL)
            {
                /* unlock previous node */
                SHIFT_STACK(&locks);
            }

            /* advance to next element in chain */
            previousNode = node;
            node         = node->next;
        }
    }

    UNROLL_STACK(&locks);

    /* not found */
    return IX_ETH_DB_NO_SUCH_ADDR;
}

IxEthDBStatus ixEthDBSearchHashEntry(HashTable *hashTable, int keyType, void *reference, HashNode **searchResult)
{
    UINT32 hashValue;
    HashNode *node;

    hashValue = hashTable->entryHashFunction(reference);
    node      = hashTable->hashBuckets[hashValue % hashTable->numBuckets];

    while (node != NULL)
    {
        TRY_LOCK(&node->lock);

        if (hashTable->matchFunctions[keyType](reference, node->data))
        {
            *searchResult = node;

            return IX_ETH_DB_SUCCESS;
        }
        else
        {
            UNLOCK(&node->lock);

            node = node->next;
        }
    }

    /* not found */
    return IX_ETH_DB_NO_SUCH_ADDR;
}

IxEthDBStatus ixEthDBPeekHashEntry(HashTable *hashTable, int keyType, void *reference)
{
    UINT32 hashValue;
    HashNode *node;

    hashValue = hashTable->entryHashFunction(reference);
    node      = hashTable->hashBuckets[hashValue % hashTable->numBuckets];

    while (node != NULL)
    {
        TRY_LOCK(&node->lock);

        if (hashTable->matchFunctions[keyType](reference, node->data))
        {
            UNLOCK(&node->lock);

            return IX_ETH_DB_SUCCESS;
        }
        else
        {
            UNLOCK(&node->lock);

            node = node->next;
        }
    }

    /* not found */
    return IX_ETH_DB_NO_SUCH_ADDR;
}

void ixEthDBReleaseHashNode(HashNode *node)
{
    UNLOCK(&node->lock);
}

IxEthDBStatus ixEthDBInitHashIterator(HashTable *hashTable, HashIterator *iterator)
{
    iterator->bucketIndex  = 0;
    iterator->node         = NULL;
    iterator->previousNode = NULL;

    return ixEthDBIncrementHashIterator(hashTable, iterator);
}

void ixEthDBReleaseHashIterator(HashIterator *iterator)
{
    if (iterator->previousNode != NULL)
    {
        UNLOCK(&iterator->previousNode->lock);
    }

    if (iterator->node != NULL)
    {
        UNLOCK(&iterator->node->lock);
    }
}

IxEthDBStatus ixEthDBIncrementHashIterator(HashTable *hashTable, HashIterator *iterator)
{
    /* unless iterator is just initialized... */
    if (iterator->node != NULL)
    {
        /* try next in chain */
        if (iterator->node->next != NULL)
        {
            TRY_LOCK(&iterator->node->next->lock);

            if (iterator->previousNode != NULL)
            {
                UNLOCK(&iterator->previousNode->lock);
            }

            iterator->previousNode = iterator->node;
            iterator->node         = iterator->node->next;

            return IX_ETH_DB_SUCCESS;
        }
        else
        {
            /* last in chain, prepare for next bucket */
            iterator->bucketIndex++;
        }
    }

   /* try next used bucket */
    for (; iterator->bucketIndex < hashTable->numBuckets ; iterator->bucketIndex++)
    {
        HashNode **nodePtr = &(hashTable->hashBuckets[iterator->bucketIndex]);
        HashNode *node = *nodePtr;
#if (CPU!=SIMSPARCSOLARIS) && !defined (__wince)
        if (((iterator->bucketIndex & IX_ETHDB_BUCKET_INDEX_MASK) == 0) &&
            (iterator->bucketIndex < (hashTable->numBuckets - IX_ETHDB_BUCKETPTR_AHEAD)))
        {
            /* preload next cache line (2 cache line ahead) */
            nodePtr += IX_ETHDB_BUCKETPTR_AHEAD;
            __asm__ ("pld [%0];\n": : "r" (nodePtr));
        }
#endif
        if (node != NULL)
        {
            TRY_LOCK(&node->lock);

            /* unlock last one or two nodes in the previous chain */
            if (iterator->node != NULL)
            {
                UNLOCK(&iterator->node->lock);

                if (iterator->previousNode != NULL)
                {
                    UNLOCK(&iterator->previousNode->lock);
                }
            }
            
            /* redirect iterator */
            iterator->previousNode = NULL;
            iterator->node         = node;

            return IX_ETH_DB_SUCCESS;
        }
    }

    /* could not advance iterator */
    if (iterator->node != NULL)
    {
        UNLOCK(&iterator->node->lock);

        if (iterator->previousNode != NULL)
        {
            UNLOCK(&iterator->previousNode->lock);
        }

        iterator->node = NULL;
    }

    return IX_ETH_DB_END;
}

IxEthDBStatus ixEthDBRemoveEntryAtHashIterator(HashTable *hashTable, HashIterator *iterator)
{
    HashIterator nextIteratorPos;
    LockStack locks;

    INIT_STACK(&locks);

    /* set initial bucket index for next position */
    nextIteratorPos.bucketIndex = iterator->bucketIndex;

    /* compute iterator position before removing anything and lock ahead */
    if (iterator->node->next != NULL)
    {
        PUSH_LOCK(&locks, &iterator->node->next->lock);

        /* reposition on the next node in the chain */
        nextIteratorPos.node         = iterator->node->next;
        nextIteratorPos.previousNode = iterator->previousNode;
    }
    else
    {
        /* try next chain - don't know yet if we'll find anything */
        nextIteratorPos.node = NULL;

        /* if we find something it's a chain head */
        nextIteratorPos.previousNode = NULL;

        /* browse up in the buckets to find a non-null chain */
        while (++nextIteratorPos.bucketIndex < hashTable->numBuckets)
        {
            nextIteratorPos.node = hashTable->hashBuckets[nextIteratorPos.bucketIndex];

            if (nextIteratorPos.node != NULL)
            {
                /* found a non-empty chain, try to lock head */
                PUSH_LOCK(&locks, &nextIteratorPos.node->lock);

                break;
            }
        }
    }

    /* restore links over the to-be-deleted item */
    if (iterator->previousNode == NULL)
    {
        /* first in chain, lock bucket */
        PUSH_LOCK(&locks, &hashTable->bucketLocks[iterator->bucketIndex]);

        hashTable->hashBuckets[iterator->bucketIndex] = iterator->node->next;

        POP_LOCK(&locks);
    }
    else
    {
        /* relink */
        iterator->previousNode->next = iterator->node->next;

        /* unlock last remaining node in current chain when moving between chains */
        if (iterator->node->next == NULL)
        {
            UNLOCK(&iterator->previousNode->lock);
        }
    }

    /* delete entry */
    hashTable->freeFunction(iterator->node->data);
    ixEthDBFreeHashNode(iterator->node);

    /* reposition iterator */
    *iterator = nextIteratorPos;

    return IX_ETH_DB_SUCCESS;
}

