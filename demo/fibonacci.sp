class Test {
    var number
    new(a) {
        // System.print("init")
        // System.print(a)
        number = a
        // System.print(number)
    }

    number {
        return number
    }

    fib() {
        var res = fibonacci(number)
        // System.print(res)
        return res
    }

    fibonacci(num) {

        // System.print(num)
        if(num == 0) {
            return 0
        }

        if(num == 1 || num == 2) {
            return 1
        }

        // var temp1 = fibonacci(num - 2)
        // var temp2 = fibonacci(num - 1)

        // System.print(num.toString + " temp1 " + temp1.toString)
        // System.print(num.toString + " temp2 " + temp2.toString)

        // return temp1 + temp2

        return fibonacci(num - 2) + fibonacci(num - 1)
    }
}

/*
fun foo() {
    var i = 40
    // System.print(i)

    var t = Test.new(i)

    // System.print(t)

    System.print(t.number)

    var res = t.fib()

    System.print(res)

}

foo()
*/


fun foo() {
    var i = 20
    while (i < 40)  {
        // System.print(i)
        i = i + 1

        var t = Test.new(i)

        // System.print(t)

        var startTIme = System.clock

        var res = t.fib()

        var endTIme = System.clock

        System.print(t.number.toString + ": " + res.toString + " time:" + ((endTIme - startTIme) / 1000).toString + " ms")
    }
}

foo()



/*
class Employee {
   var name
   var gender
   var age
   var salary
   static var employeeNum = 0
   new(n, g, a, s) {
      name = n
      gender = g
      age = a
      salary = s
      employeeNum = employeeNum + 1
   }

   sayHi() {
      System.print("My name is " + 
	    name + ", I am a " + gender + 
	    ", " + age.toString + "years old") 
   }

   salary {
      return salary
   }

   static employeeNum {
      return employeeNum
   }
}
*/

