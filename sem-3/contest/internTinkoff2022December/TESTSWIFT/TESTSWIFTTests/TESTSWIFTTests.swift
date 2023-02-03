
//  TESTSWIFTTests.swift
//  TESTSWIFTTests
//
//  Created by Grigorii Rassadnikov on 21.12.2022.
//

import XCTest
@testable import TESTSWIFT

final class TESTSWIFTTests: XCTestCase {
    
    func test1(){
        let yetAnotherPoint = (1, -1)
        switch yetAnotherPoint {
        case let (x, y) where x == y:
            print("(\(x), \(y)) is on the line x == y")
        case let (x, y) where x == -y:
            print("(\(x), \(y)) is on the line x == -y")
        case let (x, y):
            print("(\(x), \(y)) is just some arbitrary point")
        }
//        (1, -1) is on the line x == -y
    }
    
    func test2(){
//        Чему равен result?
        let temperatureInFahrenheit = 25
        var result = 5
        if temperatureInFahrenheit <= 20 {
            result = result + 6
        } else if temperatureInFahrenheit >= 30 {
            result = result + 7
        } else {
            result = result + 8
        }
        print(result)
//        13
    }
    
    func test3(){
//        Чему равно значение переменной answer?
        let base = 1
        let power = 3
        var answer = 1
        for _ in 1...power {
            answer *= base
        }
        print(answer)
//        1
    }
    
    func test4(){
//        Чему равно значение переменной i?
        var i = 2
        while i < 3 {
        i += 1
        }
        print(i)
//        3
    }
    
    func test5(){
//        Что напечатается в консоль?

        let a = true
        let b = true
        let c = false
        if a && c {
        print ("a")
        } else {
            if a || c {
                print ("c")
            } else {
                print ("b")
            }
        }
//        c
    }
    
    func test6(){
//        Что напечатается в консоль?

        let a = "Hello World!"
        let b = "Hello World!"
        if a == b {
            print("These two strings are considered equal")
        }
//        These two strings are considered equal
    }
    
    func test7(){
//        Чему равно значение переменной a?

        func customFunc(value: Int) -> Int {
            return value * 5
        }
        let a = customFunc(value: 10)
        print(a)
//        50
    }
    
    func test8(){
//        Числовой массив А заполнен последовательно числами: 2, 5, 7, 34. Укажите
//        значение элемента А[2].
        
//        7
    }
    
    func test9(){
//        Какое ключевое слово используется для доступа к методам и свойствам суперкласса
        
//        self
    }
    
    func test10(){
//        Чему равно значение переменной f?

        let a = 10
        let b = 4
        let c = 9
        let d = 3
        let e = (a - b) * c / d
        let f = e % 5
        print(f)
        
//        3
    }
    
    func test11(){
//        Что напечатается в консоль?

        let a = 2
        let b = 1
        let string = "string1"
        if a > b {
            if string == "string" {
                print("a")
            } else {
                print("b")
            }
        } else {
            print("c")
        }
        
//        b
    }
    
    func test12(){
//        Чему равно значение переменной?

        var a = 0
        for i in 1...5 {
        if i > 2 {
        break
        }
        a += 1
        }
        print(a)
        
//        2
        
    }
    
    func test13(){
//        Чему равно значение a?

        var a = 1
        a += 2
        print(a)
//        3
    }
    
    func test14(){
//        Как называется представленный способ извлечения optional value?

        var a: Int? = nil
        let b = a ?? 5
    }
    
    func test15(){
//        Что напечатается в консоль?

        struct MyStruct {
            static var helloWorld = "HelloWorld"
            var name: String
            var age: Int
        }
        
        let a = MyStruct(name: "James", age: 25)
//        print(a.helloWorld)
//        Этот код не скомпилируется


    }
    
    func test16(){
//        Что напечатается в консоль?

        func sendToServer(name: String?, address: String?, phone: String?) {
            guard let name = name else {
                print("No name to submit")
                return
            }
            guard let address = address else {
                print("No address to submit")
                return
            }
            guard let phone = phone else {
                print("No phone to submit")
                return
            }
        }
        sendToServer(name: nil, address: "13", phone: "fg")
//        No name to submit
    }
    
    func test17(){
//        К какому типу относится свойство totalSteps?

        class StepCounter {
            var totalSteps: Int = 0 {
                willSet(newTotalSteps) {
                    print("About to set totalSteps to \(newTotalSteps)")
                }
                didSet {
                    if totalSteps > oldValue {
                        print("Added \(totalSteps - oldValue) steps")
                    }
                }
            }
        }
    }
    
    func test18(){
//        Чему равно значение переменной a?

        func someFunction(a: Bool) -> (Int) -> Int {
            func someFunction1(a: Int) -> Int { return a + 1 }
            func someFunction2(a: Int) -> Int { return a - 1 }
            return a ? someFunction1 : someFunction2
        }
        let function = someFunction(a: true)
        let a = function(3)
        print(a)
//        4
    }
    
    func test19(){
//        Чему равно значение массива numbers?

        let numbers = [1, 2, 3].flatMap { [$0, $0] }
        print(numbers)
//        [1, 1, 2, 2, 3, 3]
    }
    
    func test20(){
//        Предполагая, что нельзя использовать приведение типов, какое изутверждений верно?

        var foo: Float = 32
        var bar: Double = 32
        
        bar = foo as! Double
        
//       никакие
    }
    
    func test21(){
//        Что напечатается в консоль?

        enum MyError: Error {
            case broken
            case busted
            case badgered
        }
        func willThrowAnError() throws {
            throw MyError.busted
        }
        do {
            try willThrowAnError()
        } catch MyError.busted {
            print("Code was busted!")
        } catch {
            print("Code just didn't work")
        }
//        Code was busted!
    }
    
    func test22(){
//        Выберите правильную сигнатуру метода, который в качестве параметра принимает
//        generic type



//         generic func genericFunction(argument: T) { }
//         func genericFunction<T>(argument) { }
//         func genericFunction(argument: T<Generic>) { }
//         + func genericFunction<T>(argument: T) { }


    }
    
    func test23(){
        
    }
    
    func test24(){
//        Что напечатается в консоль?

        let names: [String?] = ["Barbara", nil, "Janet", nil, "Peter", nil,
        "George"]
        if let firstName = names.first {
            print(firstName)
        }
//        Optional("Barbara")
    }
    
    func test25(){
        
    }
    
    func test26(){
//        Какой паттерн гарантирует, что класс имеет только один экземпляр и предоставляет единую точку доступа к нему

//         синглтон
//         фасад
//         прототип
//         прокси
    }
    
    func test27(){
//        Выберите правильную команду для добавления сообщения к коммиту

//         git message "I'm coding"
//         git add "I'm coding"
//         git commit "I'm coding"
//         + git commit -m "I'm coding"
    }
    
    func test28(){
//        Какая команда используется для слияния веток?
//         merge
//        add
//        pull
//         tag
    }
    
    func test29(){
//        Какой паттерн определяет группу алгоритмов, инкапсулирует их и делает
//        взаимозаменяемыми. Также позволяет изменять алгоритм независимо от клиентов,
//        которые его используют?
//
//         Стратегия
//         Состояние
//         Интепритатор
//        Декоратор
    }
    
    func test30(){
//        Обеспечение доступности главного и ограничение от деталей, ближе к понятию …
//
//         Полиморфизм
//         Наследование
//         Инкапсуляция
//         Делегирование
    }
    
    func test31(){
//        Полиморфизм $-$ это
//
//         Свойство объекта изменять поведение полученное от родительского класса
//         Передача реализации функциональности другому классу
//         Приобретение функциональности родительского класса
//         Сокрытие деталей реализации в рамках класса
//

    }
    
    func test32(){
//        Выразите -7, как 16bit знаковое число
//
//        0000 0000 0000 0111
//        1111 1111 1111 1001
//        0111 0000 0000 0001
//        0111 0000 0000 0000
        func byteArray<T>(from value: T) -> [UInt8] where T: FixedWidthInteger {
            withUnsafeBytes(of: value.bigEndian, Array.init)
        }
        print(byteArray(from: Int16(-7)))
    }
    
    func test33(){
//        Умножьте два числа в двоичной системе счисления $11011*101$
//        10000111
//        11111111
//        11011101
//        10011111
    }
    
    func test34(){
//        Какая из следующих хэш-функций для int распределится более равномерно по 10 бакетам от 0 до 9 для i от 0 до 2020
//
//         h(i) = i^2 mod 10
//         h(i) = i^3 mod 10
//         h(i) = (11 * i^2) mod 10
//         h(i) = (12 * i) mod 10
        var a = [Int](repeating: 0, count: 10)
        for i in 1..<2020+1 {
            var h = (i*i*i)%10
            a[h]+=1
        }
        print(a)
    }
    func test35(){
//        Какая из следующих операций не O(1) для отсортированного массива, каждый элемент
//        массива уникален
//
//         Поиск максимального элемента
//         Удаление элемента
//         Поиск минимального элемента
//         Все вышеперечисленное
    }
    func test36(){
//        Какой из следующих алгоритмов сортировки дает большую производительность на массиве в котором все элементы почти в отсортированном порядке (1 или 2 элемента не на своих местах)
//
//         Сортировка вставкой
//         Сортировка слиянием
//         Быстрая сортировка
//         Пузырьковая сортировка

    }
}

