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


# Delete the provided node if it is not the last node.
#
# time complexity: O(1)
# space complexity: O(1)
def delete_node(node: ListNode) -> bool:
    if not node or not node.next:
        return False

    # Delete next node and copy the data from it to here.
    next = node.next
    node.value = next.value
    node.next = next.next
    return True


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


class DeleteNodeTest(unittest.TestCase):
    def test_delete_node(self):

        test_cases = [
            ([], 1, [], False),
            ([1], 0, [1], False),
            ([1, 2], 0, [2], True),
            ([1, 2], 1, [1, 2], False),
            ([1, 2, 3, 4], 0, [2, 3, 4], True),
            ([1, 2, 3, 4], 1, [1, 3, 4], True),
            ([1, 2, 3, 4], 2, [1, 2, 4], True),
            ([1, 2, 3, 4], 3, [1, 2, 3, 4], False),
        ]
        for values, i, result, expected in test_cases:
            l = make_list(values)
            to_delete = get_ith_node(l, i)
            self.assertEqual(delete_node(to_delete), expected)
            self.assertTrue(list_equal(l, make_list(result)))



if __name__ == "__main__":
    unittest.main()
