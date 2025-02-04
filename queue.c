#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *q_head = malloc(sizeof(struct list_head));
    if (!q_head)
        return NULL;

    INIT_LIST_HEAD(q_head);

    return q_head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    element_t *cur, *tmp;
    list_for_each_entry_safe (cur, tmp, l, list) {
        q_release_element(cur);
    }

    free(l);
    return;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *new_node = malloc(sizeof(element_t));

    if (!new_node)
        return false;

    new_node->value = (char *) malloc(sizeof(char) * strlen(s) + 1);

    if (!new_node->value) {
        free(new_node);
        return false;
    }

    strncpy(new_node->value, s, strlen(s) + 1);
    list_add(&new_node->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *new_node = malloc(sizeof(element_t));

    if (!new_node)
        return false;

    new_node->value = (char *) malloc(sizeof(char) * strlen(s) + 1);

    if (!new_node->value) {
        free(new_node);
        return false;
    }

    strncpy(new_node->value, s, strlen(s) + 1);
    /* need INIT_LIST_HEAD() when use list add tail */

    list_add_tail(&new_node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *f_node = list_first_entry(head, element_t, list);
    list_del(&f_node->list);
    if (sp) {
        strncpy(sp, f_node->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }

    return f_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *l_node = list_last_entry(head, element_t, list);
    list_del(&l_node->list);
    if (sp) {
        strncpy(sp, l_node->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }

    return l_node;
}

/* Return number of elements in queue
 * Return 0 if q is NULL or empty
 */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *trv_forward = head->next;
    struct list_head *trv_backward = head->prev;
    while (trv_backward->next != trv_forward && trv_backward != trv_forward) {
        trv_forward = trv_forward->next;
        trv_backward = trv_backward->prev;
    }
    list_del(trv_backward);

    /**
     * It can be `q_release_element(list_entry(trv_backward, element_t, list);`
     * but this may more readable.
     */
    element_t *middle = list_entry(trv_backward, element_t, list);
    q_release_element(middle);
    return true;
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head) || list_is_singular(head))
        return;

    struct list_head *node, *tmp;
    list_for_each_safe (node, tmp, head) {
        list_move(node, head);
    }
    return;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}