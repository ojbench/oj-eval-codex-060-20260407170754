# Problem 060 - Validator Lite

**ACMOJ Problem ID**: 2392

## Table of Contents

- [Problem 060 - Validator Lite](#problem-060-validator-lite)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Implement chainable parameter validator with method chaining. Supports range checks, not-equal, string length validation.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2392. Validator Lite** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/060/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

**注意：这是一道工程题。**

在暑假的的PPCA这门课中，Hartmann没能选上Pacman项目，而是十分不幸地被扔到了Coq Formal Verification小组。你说得对，但这就是我们Coq语言人工智障的nia / tauto自动推理，用"."代替";"作为语句结尾的构式词法，递归平替一切循环的神人语法，以及超越一切其他小组的超绝码量。写一门图灵不完备的语言导致的。

尽管有着这么多的问题，Coq仍然有一个好处：支持识别形如$a\le b\le c$的连续不等式。Hartmann觉得这是一个极好的feature，同时贴心地考虑到你们将来的Bookstore大作业中有许多参数验证，也许会想要用到类似的参数验证方法，于是将其编成了一道题目。

本任务要求你实现一个这样的`expect`函数，若验证不通过则返回`false`，否则返回`true`。它只有一个输入参数，其他参数以*链式调用 (method chaining)* 的方式传入。例如，如果想要验证某个`int`类型的变量$num$的值满足$114\le num\lt 514$且$num\ne 321$，就可以写成：

```
if (expect(num).ge(114).lt(514).Not().toBe(321)) {
  // ...
}
```
效果等价于：
```
if (num >= 114 && num < 514 && num != 321) {
  // ...
}
```

`expect`函数传入的参数可以是任意类型，保证传入的类型重载了`=`，`==`与`<`运算符和拷贝构造函数。此外，你需要实现如下功能：
```
// 验证是否有 x == y
expect(x).toBe(y);

// 验证 y 中是否存在元素 z，使得 x == z
// 若 x 的类型为 T，则 y 的类型为 std::vector<T>
expect(x).toBeOneOf(y);

// 验证是否有 x <= y 或 x >= y
expect(x).le(y);
expect(x).ge(y);

// 验证是否有 x < y 或 x > y
expect(x).lt(y);
expect(x).gt(y);

// 将后面跟的所有条件取反
expect(x).Not();
```
下面用一个例子来帮助你更好地理解 `Not()` 的功能：
```
// 意为 x 不能为 1 且不能为 2
expect(x).Not().toBe(1).toBe(2);
```

另外，`expect`链式调用的所有条件以与的方式连接。换句话说，如果把`expect`函数转写成等价的布尔表达式，那么所有的子表达式都是以`&&`连接的。

### 注意事项
**请勿在你提交的代码中使用任何头文件**，除了`<vector>`。**请勿**在你的代码中添加`using namespace std;`语句。违反此条事项的提交将会被置`void`。

如果你使用了`new`表达式或`malloc()`函数，请注意进行内存管理，本题中的一些数据点将会检测内存泄漏情况。


### 一些提示
- 你可能需要定义一个结构体模板，作为`expect`函数的返回类型。
- 你可以为模板添加重载布尔类型转换的函数。添加了此函数之后，在需要类型转换时（例如`expect`函数的返回值作为`if`语句的条件表达式），编译器就会自动调用类型转换函数，将结构体转换为`bool`类型。
重载类型转换函数的语法如下：
```
template <typename T> struct E {

  operator bool() const {
    // TODO: Implement this function
    return true;
  }
};
```

### 评测方式
你提交的代码中需要实现以上的全部接口。提交之后，你的代码将会作为`src.hpp`被云端的`main.cpp`调用。因此，你的代码中**不应该含有`main`函数**。

### Input Format

See the problem description above.

### Output Format

See the problem description above.

### Samples

#### Sample 1

### Data Constraints

- 对于 testpoint 1-3，输入参数类型固定为`int`：
  - testpoint 1：仅`le()`，`lt()`，`ge()`，`gt()`；
  - testpoint 2：仅`toBe()`，`toBeOneOf()`；
  - testpoint 3：所有接口。
- 对于 testpoint 4：输入参数类型固定为`std::string`；
- 对于 testpoint 5-6：无限制；
- 对于 testpoint 7-9：内容与testpoint 1-3 一致，启用内存泄漏检测。
* For all testpoints：保证不会出现仅调用 `expect(x)` 而不后随任何链式调用的情况

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 10000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/060/data_test/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
