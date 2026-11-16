class Node:
    """Node class for the linked list"""
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    """Singly Linked List class"""
    def __init__(self):
        self.head = None
        self.size = 0

    # Insert at the beginning
    def add_first(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
        self.size += 1

    # Insert at the end
    def add_last(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
        else:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = new_node
        self.size += 1

    # Insert at a specific position
    def add_at(self, data, pos):
        if pos < 0 or pos > self.size:
            print("Invalid position!")
            return
        if pos == 0:
            self.add_first(data)
            return
        new_node = Node(data)
        temp = self.head
        for _ in range(pos - 1):
            temp = temp.next
        new_node.next = temp.next
        temp.next = new_node
        self.size += 1

    # Remove from the beginning
    def remove_first(self):
        if not self.head:
            return
        self.head = self.head.next
        self.size -= 1

    # Remove from the end
    def remove_last(self):
        if not self.head:
            return
        if not self.head.next:
            self.head = None
        else:
            temp = self.head
            while temp.next.next:
                temp = temp.next
            temp.next = None
        self.size -= 1

    # Remove from a specific position
    def remove_at(self, pos):
        if pos < 0 or pos >= self.size:
            print("Invalid position!")
            return
        if pos == 0:
            self.remove_first()
            return
        temp = self.head
        for _ in range(pos - 1):
            temp = temp.next
        temp.next = temp.next.next
        self.size -= 1

    # Print the list
    def print_list(self):
        temp = self.head
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("None")

# Example usage
if __name__ == "__main__":
    lst = LinkedList()
    lst.add_first(10)
    lst.add_last(20)
    lst.add_last(30)
    lst.add_at(15, 1)  # Insert 15 at position 1
    lst.print_list()   # Output: 10 -> 15 -> 20 -> 30 -> None

    lst.remove_at(1)   # Remove value at position 1 (15)
    lst.print_list()   # Output: 10 -> 20 -> 30 -> None

    lst.remove_first() # Remove first node
    lst.print_list()   # Output: 20 -> 30 -> None

    lst.remove_last()  # Remove last node
    lst.print_list()   # Output: 20 -> None
