import unittest

class ListNode:
    def __init__(self, value=None):
        self.value = value
        self.next = None

    def __str__(self):
        res = f"('{self.value}'"
        it = self.next
        while it:
            res += f"->'{it.value}'"
            it = it.next
        res += ")"

        return res

    def to_list(self):
        res = [self.value]
        it = self.next
        while it:
            res.append(it.value)
            it = it.next

        return res


# Partition list around the given partition value.
#
# time complexity: O(N)
# space complexity: O(N)
def partition(node: ListNode, val) -> bool:
    if not node:
        return node

    head = node
    tail = node

    while node:
        next = node.next
        if node.value < val:
            node.next = head
            head = node
        else:
            tail.next = node
            tail = node

        node = next

    tail.next = None

    return head



# test implementation

# Create a singly linked list from given array.
def make_list(values) -> ListNode:
    if not values:
        return None

    head = ListNode(values[0])
    current_node = head

    for value in values[1:]:
        current_node.next = ListNode(value)
        current_node = current_node.next

    return head

# Check if two singly linked lists are equal.
def list_equal(node1: ListNode, node2: ListNode):
    if not node1 and not node2:
        return True
    elif node1 and not node2:
        return False
    elif node2 and not node1:
        return False

    it1 = node1
    it2 = node2

    while it1 and it2:
        if it1.value != it2.value:
            return False

        it1 = it1.next
        it2 = it2.next

    return it1 == it2

# Return the ith node from given list.
def get_ith_node(head: ListNode, ith: int) -> ListNode:
    if ith < 0:
        return None

    it = head
    for i in range(ith):
        if not it:
            return None
        it = it.next

    return it


def is_partitioned(lst, val):
    if not lst:
        return True

    # Finding the partition index
    partition_index = None
    for i, value in enumerate(lst):
        if value > val:
            partition_index = i
            break

    # If all elements are less than or equal to the partition value
    if partition_index is None:
        return True

    # Check if all elements after the partition index are greater than the partition value
    return all(value > val for value in lst[partition_index:])


class DeleteNodeTest(unittest.TestCase):
    def test_delete_node(self):

        test_cases = [
            ([], 1),
            ([1, 10, 10, 1, 10], 5),
            ([1, 1, 1, 1, 1], 5),
            ([10, 10, 10, 10, 10], 5),
            ([5, 5, 5, 5, 5], 5),
        ]
        for values, pval in test_cases:
            l = make_list(values)
            if l:
                result = partition(l, pval).to_list()
                self.assertTrue(is_partitioned(result, pval))
            else:
                self.assertEqual(len(values), 0)



if __name__ == "__main__":
    unittest.main()
