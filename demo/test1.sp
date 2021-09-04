fun fibonacci(num) {

    System.print(num)
    if(num == 0) {
    return 0
    }

    if(num == 1 || num == 2) {
    return 1
    }

    var temp1 = fibonacci(num - 2)
    var temp2 = fibonacci(num - 1)

    System.print(num.toString + " temp1 " + temp1.toString)
    System.print(num.toString + " temp2 " + temp2.toString)

    return temp1 + temp2

    // return fibonacci(num - 2) + fibonacci(num - 1)
}

fun foo() {
    var res = fibonacci(10)
    System.print(res)
    return res
}

var res = foo()

System.print(res)

