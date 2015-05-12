#include "list/dlinked_list.h"
#include "CUnit/Util.h"
#include "CUnit/Basic.h"


/*===========================================================================*
 *        Definition for the test cases of the primitive input suite         *
 *===========================================================================*/
void TestPrimPushFront();
void TestPrimPushBack();
void TestPrimInsertForward();
void TestPrimInsertBackward();


int32_t SuitePrimitive()
{
    CU_pSuite pSuite = CU_add_suite("Primitive Input", NULL, NULL);
    if (!pSuite)
        return ERR_NOMEM;

    CU_pTest pTest = CU_add_test(pSuite, "Basic item prepending", TestPrimPushFront);
    if (!pTest)
        return ERR_NOMEM;

    pTest = CU_add_test(pSuite, "Basic item appending", TestPrimPushBack);
    if (!pTest)
        return ERR_NOMEM;

    pTest = CU_add_test(pSuite, "Basic forward item insertion", TestPrimInsertForward);
    if (!pTest)
        return ERR_NOMEM;

    pTest = CU_add_test(pSuite, "Basic backward item insertion", TestPrimInsertBackward);
    if (!pTest)
        return ERR_NOMEM;

    return SUCC;
}


int32_t main()
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();
    assert(CU_get_registry() != NULL);
    assert(!CU_is_test_running());

    /* Prepare the test suite for primitive input. */
    if (SuitePrimitive() != SUCC) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Launch all the tests. */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return SUCC;
}


/*===========================================================================*
 *      Implementation for the test cases of the primitive input suite       *
 *===========================================================================*/
void TestPrimPushFront()
{
    DLinkedList *pList;
    CU_ASSERT(DListInit(&pList) == SUCC);

    /* Prepend the items. */
    CU_ASSERT(pList->push_front(pList, (Item)4) == SUCC);
    CU_ASSERT(pList->push_front(pList, (Item)3) == SUCC);
    CU_ASSERT(pList->push_front(pList, (Item)2) == SUCC);
    CU_ASSERT(pList->push_front(pList, (Item)1) == SUCC);

    /* Check the item insertion sequence. */
    Item item;
    CU_ASSERT(pList->get_front(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_back(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, 0) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, 1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, 2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, 3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, -4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, -3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, -2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, -1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    /* Check the list size. */
    CU_ASSERT_EQUAL(pList->size(pList), 4);

    DListDeinit(&pList);
}

void TestPrimPushBack()
{
    DLinkedList *pList;
    CU_ASSERT(DListInit(&pList) == SUCC);

    /* Prepend the items. */
    CU_ASSERT(pList->push_back(pList, (Item)1) == SUCC);
    CU_ASSERT(pList->push_back(pList, (Item)2) == SUCC);
    CU_ASSERT(pList->push_back(pList, (Item)3) == SUCC);
    CU_ASSERT(pList->push_back(pList, (Item)4) == SUCC);

    /* Check the item insertion sequence. */
    Item item;
    CU_ASSERT(pList->get_front(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_back(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, 0) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, 1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, 2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, 3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, -4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, -3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, -2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, -1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    /* Check the list size. */
    CU_ASSERT_EQUAL(pList->size(pList), 4);

    DListDeinit(&pList);
}

void TestPrimInsertForward()
{
    DLinkedList *pList;
    CU_ASSERT(DListInit(&pList) == SUCC);

    /* Insert the items. */
    CU_ASSERT(pList->insert(pList, (Item)1, 0) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)4, 1) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)2, 1) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)3, 2) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)0, 0) == SUCC);

    /* Check the item insertion sequence. */
    Item item;
    CU_ASSERT(pList->get_front(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_back(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, 0) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_at(pList, &item, 1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, 2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, 3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, 4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, -5) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_at(pList, &item, -4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, -3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, -2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, -1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    /* Check the list size. */
    CU_ASSERT_EQUAL(pList->size(pList), 5);

    DListDeinit(&pList);
}

void TestPrimInsertBackward()
{
    DLinkedList *pList;
    CU_ASSERT(DListInit(&pList) == SUCC);

    /* Insert the items. */
    CU_ASSERT(pList->insert(pList, (Item)4, 0) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)1, -1) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)3, -1) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)2, -2) == SUCC);
    CU_ASSERT(pList->insert(pList, (Item)0, -4) == SUCC);

    /* Check the item insertion sequence. */
    Item item;
    CU_ASSERT(pList->get_front(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_back(pList, &item) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, 0) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_at(pList, &item, 1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, 2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, 3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, 4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    CU_ASSERT(pList->get_at(pList, &item, -5) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)0);
    CU_ASSERT(pList->get_at(pList, &item, -4) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)1);
    CU_ASSERT(pList->get_at(pList, &item, -3) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)2);
    CU_ASSERT(pList->get_at(pList, &item, -2) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)3);
    CU_ASSERT(pList->get_at(pList, &item, -1) == SUCC);
    CU_ASSERT_EQUAL(item, (Item)4);

    /* Check the list size. */
    CU_ASSERT_EQUAL(pList->size(pList), 5);

    DListDeinit(&pList);
}