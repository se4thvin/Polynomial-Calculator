# Polynomial Expression Evaluator

This program implements a linked list to evaluate polynomial expressions, designed as part of a physics engine for a new game in the Doom franchise. It demonstrates key concepts like object-oriented programming, operator overloading, recursive algorithms, and dynamic data structures.

---

## Objectives

- Implement a linked list using classes.
- Create multiple classes that interact with each other.
- Overload operators for custom functionality.
- Implement recursive algorithms on a linked list.

---

## Features

1. **Node Class**
   - **Attributes**:
     - `Coef` (double): Coefficient of the term.
     - `Exp` (int): Exponent of the term.
     - `Next` (Node pointer): Pointer to the next node in the list.
   - **Methods**:
     - Default and overloaded constructors.
     - Accessor and mutator methods.
     - Overloaded stream operator (`<<`) to display terms in the format `<coefficient>x^<exponent>`.

2. **LinkedList Class**
   - **Attributes**:
     - `Head` (Node pointer): Pointer to the first node in the list.
     - `Size` (int): Number of nodes in the list.
   - **Methods**:
     - Default constructor and destructor (recursive deletion).
     - Accessor and mutator methods.
     - Overloaded operators:
       - `[]`: Access a node at a specific index. Returns `nullptr` if index is invalid.
       - `+=`: Add a node to the end of the list.
       - `<<`: Display the entire list in a readable format.
     - `sortList`: Sort the nodes in descending order by exponent. **Does not swap data between nodes**.

---

## Input Format

- Each line of the input file contains a polynomial expression in the format:
- f()= - `<number>`: A value (integer or floating-point) used to evaluate the expression.
- `<expression>`: A polynomial expression consisting of terms in the form `ax^b`, where:
  - `a` (optional): Coefficient (integer or floating-point). Defaults to `1` if absent.
  - `b` (optional): Exponent. Defaults to `1` if absent.
  - If a term lacks `x` or `^`, it is treated as a constant.

---

## Output Format

- Each line in the console will contain:- `<expression>`: The original expression in **standard form** (sorted by descending exponent).
  - If the coefficient is `1`, it is not displayed.
  - If the exponent is `0`, the term is displayed as a constant.
  - First negative terms do not have a space between the sign and coefficient.
- `<value>`: The evaluated result, rounded to 3 decimal places.

---

## Program Details

### Node Class

#### Attributes
- `Coef` (double)
- `Exp` (int)
- `Next` (Node pointer)

#### Methods
- Constructors:
- Default constructor.
- Overloaded constructor: Accepts coefficient and exponent.
- Accessors and mutators.
- Overloaded stream operator (`<<`): Displays nodes in the format `<coefficient>x^<exponent>`.

### LinkedList Class

#### Attributes
- `Head` (Node pointer)
- `Size` (int)

#### Methods
- Default constructor.
- Destructor: Recursively deletes all nodes.
- Accessors and mutators.
- Overloaded operators:
- `[]`: Access a node by index. Returns `nullptr` if index is invalid.
- `+=`: Add a new node to the end of the list.
- `<<`: Print the entire list.
- `sortList`: Sorts the linked list by descending exponent (node swapping only).

---

## Main Function Workflow

1. Prompt the user for the filename containing polynomial expressions.
2. Read and parse each line of the file.
3. Construct the linked list by:
 - Parsing terms and creating nodes.
 - Adding nodes to the list using the `+=` operator.
4. Sort the linked list in descending order by exponent.
5. Evaluate the polynomial at the specified value.
6. Display the original expression in standard form and the evaluated result.

### Supporting Functions
- **Parsing Function**:
- **Parameters**: Input string.
- **Return**: Parsed coefficient, exponent, and value.
- **Logic**: Extract terms, handle missing coefficients or exponents, and normalize the format.
- **Evaluation Function**:
- **Parameters**: A linked list and a value to evaluate.
- **Return**: The evaluated result.
- **Logic**: Traverse the list, calculate the value for each term, and sum them up.
