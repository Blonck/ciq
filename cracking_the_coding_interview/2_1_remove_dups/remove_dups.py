import unittest

class ListNode:
    def __init__(self, value=None):
        self.value = value
        self.next = None


# Remove all duplicates from given unsorted list.
#
# time complexity: O(N)
# space complexity: O(1)
def delete_dups(node: ListNode):
    seen = set()

    prev = None
    while node:
        if node.value in seen:
            prev.next = node.next
        else:
            seen.add(node.value)
            prev = node
        node = node.next


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


class DeleteDupsTest(unittest.TestCase):
    def test_delete_dups(self):

        test_cases = [
            (make_list([]), make_list([])),
            (make_list([1]), make_list([1])),
            (make_list([1, 2, 3]), make_list([1, 2, 3])),
            (make_list([1, 1, 1]), make_list([1])),
            (make_list([1, 1, 2, 2, 3, 3]), make_list([1, 2, 3])),
            (make_list([1, 2, 3, 1, 2, 3]), make_list([1, 2, 3])),
        ]
        for n1, n2 in test_cases:
            delete_dups(n1)
            self.assertTrue(list_equal(n1, n2))



if __name__ == "__main__":
    unittest.main()
