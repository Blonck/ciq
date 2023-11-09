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


# Finds the kth to the last element of the provided singly linked list.
#
# time complexity: O(N)
# space complexity: O(1)
def kth_to_last(head: ListNode, k: int) -> ListNode:
    it1 = head
    it2 = head

    # Forward it1 k times.
    for i in range(k):
        if not it1:
            return None
        it1 = it1.next

    if not it1:
        return None

    # Now it1 is k positions in advance of it2. When it1 is exhausted
    # it2 is at the kth to the last position.
    while it1.next:
        it1 = it1.next
        it2 = it2.next

    return it2

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


class KthToLastTest(unittest.TestCase):
    def test_kth_to_last(self):

        test_cases = [
            ([], 2),
            ([1], 0),
            ([1], 1),
            ([1, 2], 0),
            ([1, 2], 1),
            ([1, 2], 2),
            ([1, 2, 3, 4, 1, 2, 3, 4], 0),
            ([1, 2, 3, 4, 1, 2, 3, 4], 1),
            ([1, 2, 3, 4, 1, 2, 3, 4], 5),
            ([1, 2, 3, 4, 1, 2, 3, 4], 100),
        ]
        for values, k in test_cases:
            l = make_list(values)
            kth = kth_to_last(l, k)
            expected = get_ith_node(l, len(values) - k - 1)

            self.assertEqual(kth, expected)



if __name__ == "__main__":
    unittest.main()
