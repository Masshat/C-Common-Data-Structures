#include "cds.h"


typedef struct Employ_ {
    int8_t cYear;
    int8_t cLevel;
    int32_t iId;
} Employ;


void DestroyObject(Item item)
{
    free((Employ*)item);
}


int main()
{
    Vector *pVec;

    /* You should initialize the DS before any operations. */
    int32_t rc = VectorInit(&pVec, 1);
    if (rc != SUCC)
        return rc;

    /* If you plan to delegate the resource clean task to the DS, please set the
       custom clean method. */
    pVec->set_destroy(pVec, DestroyObject);

    /* Push the items. */
    Employ *pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 3;
    pEmploy->cLevel = 3;
    pEmploy->cYear = 3;
    pVec->push_back(pVec, (Item)pEmploy);

    pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 4;
    pEmploy->cLevel = 4;
    pEmploy->cYear = 4;
    pVec->push_back(pVec, (Item)pEmploy);

    /* Insert the items at the designated indexes. */
    pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 1;
    pEmploy->cLevel = 1;
    pEmploy->cYear = 1;
    pVec->insert(pVec, (Item)pEmploy, 0);

    pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 2;
    pEmploy->cLevel = 2;
    pEmploy->cYear = 2;
    pVec->insert(pVec, (Item)pEmploy, 1);

    /*---------------------------------------------------------------*
     * Now the vector should be: [1] | [2] | [3] | [4]               *
     *---------------------------------------------------------------*/

    /* Retrieve the items with direct indexing. */
    Item item;
    pVec->get(pVec, &item, 0);
    assert(((Employ*)item)->iId == 1);
    pVec->get(pVec, &item, 3);
    assert(((Employ*)item)->iId == 4);

    /* Replace the item with direct indexing. */
    pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 10;
    pEmploy->cLevel = 10;
    pEmploy->cYear = 10;
    pVec->set(pVec, (Item)pEmploy, 0);

    pEmploy = (Employ*)malloc(sizeof(Employ));
    pEmploy->iId = 40;
    pEmploy->cLevel = 40;
    pEmploy->cYear = 40;
    pVec->set(pVec, (Item)pEmploy, 3);

    /*---------------------------------------------------------------*
     * Now the vector should be: [10] | [2] | [3] | [40]             *
     *---------------------------------------------------------------*/

    /* Check the number of stored items and the vector capacity. */
    int32_t iSize = pVec->size(pVec);
    assert(iSize == 4);
    int32_t iCap = pVec->capacity(pVec);
    assert(iCap == 4);

    /* Delete the item at the designated index. */
    pVec->delete(pVec, 3);
    pVec->delete(pVec, 0);

    /*---------------------------------------------------------------*
     * Now the vector should be: [2] | [3]                           *
     *---------------------------------------------------------------*/

    int32_t iNum = 0;
    pVec->get(pVec, &item, 0);
    iNum += ((Employ*)item)->iId;
    pVec->get(pVec, &item, 1);
    iNum += ((Employ*)item)->iId;
    iNum *= 20;

    /* Resize the vector storage. */
    pVec->resize(pVec, iNum);

    /* Pop the rest items. */
    pVec->pop_back(pVec);
    pVec->pop_back(pVec);

    iSize = pVec->size(pVec);
    assert(iSize == 0);
    iCap = pVec->capacity(pVec);
    assert(iCap == 100);

    /* You should deinitialize the DS after all the relevant tasks. */
    VectorDeinit(&pVec);

    return SUCC;
}
