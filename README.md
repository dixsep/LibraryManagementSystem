Library Management System
Problem Definition:
Design and implement a Library Management system that caters to its registered members by cataloging and housing books that can be borrowed.

The system must provide the following functionalities:

Add books to the catalog: Every book will be added by name and author and the program must generate a unique id for it by joining the first three letters of the author’s last name to a number to create a unique key. For example, a book by Rowling would have ROW1234 as a unique Id. Also, note that the library can have more than one copy for a book.

Register and unregister users in the Library

Reservation Management system: A user should be able to make a request to borrow a book from the library.

Users can borrow books by the book id (eg - ROW1234). For the scope of problems, let's assume users are aware of book id’s.
If the book is available and not borrowed by anyone, it should be reserved to the member’s name.
If the book is already borrowed by another user, the reservation system must add the requesting member to a FIFO waitlist of reservations. When the book is returned to the library, it will not be marked as available and will be available only to the first user under the FIFO queue
If the user is the first user of the FIFO waitlist, the book can be reserved under the user’s name
Fine calculation system: A user is allowed to borrow a book only for 14 days. If this time limit is exceeded at the time of return, the system should calculate a fine of 20 rupees per day for the number of days delay.

Good To Have (Bonus):
One user should only be allowed to reserve one copy of the book
Auditing: Design should cater to following use cases:
Given a bookId, give a list of users having that book
Given a userId, list of books issued to him

Other details:
**Use of a DB is not allowed. We are expecting in-memory data structures to support the application.

Expectations:

Functionally correct code (whatever feature is completed)
Create the sample data yourself. You can put it into a file, test case or main driver program itself. Unit test cases are not expected.
Code should be demo-able.
Code should be modular. Code should have basic OO design. Please do not jam the responsibilities of one class into another.
Code should be extensible. Wherever applicable, use interfaces and contracts between different methods. It should be easy to add/remove functionality without re-writing the entire codebase.
Code should handle edge cases properly and fail gracefully.
Code should be legible and readable.
CLI, Web based application, REST API and UI are not expected.
Guidelines:

Please discuss the solution with an interviewer
Please do not access internet for anything EXCEPT syntax
You are free to use the language of your choice
All work should be your own
Please focus on the Bonus Feature only after ensuring the required features are complete and demoable
