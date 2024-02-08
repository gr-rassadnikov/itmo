package ru.ok.itmo.example

import io.reactivex.rxjava3.android.schedulers.AndroidSchedulers
import io.reactivex.rxjava3.core.Observable
import io.reactivex.rxjava3.disposables.Disposable
import io.reactivex.rxjava3.schedulers.Schedulers
import java.util.concurrent.TimeUnit

class Timer(var sleepTime: Long) {

    private var current = 0

    @Volatile
    private var isReset = true
        set(value) = synchronized(this) { field = value }

    private var disposable: Disposable? = null
    private var thread: Thread? = null


    fun threadRunner(completion: (Int) -> Unit) {
        isReset = false
        thread = Thread {
            while (!isReset && current < 100) {
                Thread.sleep(sleepTime)
                current++
                completion(current)
            }
        }
        thread?.start()
    }

    fun observableRunner(completion: (Int) -> Unit) {
        if (disposable == null || disposable?.isDisposed == true) {
            isReset = false
            observeOnMain(completion)
        }
    }

    fun reset() {
        isReset = true
        current = 0
        disposable?.dispose()
    }

    fun end() {
        reset()
        thread?.interrupt()
    }

    private fun observeOnMain(completion: (Int) -> Unit){
        disposable = Observable.interval(sleepTime, TimeUnit.MILLISECONDS)
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
            .takeWhile { !isReset && current < 100 }
            .subscribe {
                current++
                completion(current)
            }
    }
}
