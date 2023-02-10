;-----------10-----------
(defn globalOperation [operation]
  (fn [& arguments]
    (fn [args] (apply operation (mapv
                                  (fn [functional] (functional args)) arguments)))))
(def add (globalOperation +))
(def subtract (globalOperation -))
(def multiply (globalOperation *))
(def divide (globalOperation #(/ (double %1) (double %2))))
(def negate (globalOperation -))
(defn constant [value] (fn [_] value))
(defn variable [var] (fn [value] (value var)))

(def pow (globalOperation #(Math/pow %1 %2)))
(def log (globalOperation #(/ (Math/log (Math/abs %2)) (Math/log (Math/abs %1)))))

(def operations {'+      add
                 '-      subtract
                 '*      multiply
                 '/      divide
                 'negate negate
                 'pow    pow
                 'log    log})


(defn parseExpression [expression]
  (cond
    (symbol? expression) (variable (str expression))
    (number? expression) (constant (long expression))
    :else (apply (get operations (first expression)) (mapv parseExpression (rest expression)))))

(defn parseFunction [str] (parseExpression (read-string str)))

;---------11-----------
(load-file "proto.clj")

(def toString (method :toString))
(def evaluate (method :evaluate))
(def diff (method :diff))
(def operands (field :arguments))
(def toStringSuffix (method :toStringSuffix))

(defn valueConstructor [operation d]
  (fn [value]
    {:toString       (fn [_] (str value))
     :evaluate       operation
     :diff           d
     :arguments      value
     :toStringSuffix (fn [_] (str value))})
  )

(defn binary [opStr operation d]
  (fn [first second]
    {:toString       (fn [_] (str "("
                                  opStr
                                  " "
                                  (toString first)
                                  " "
                                  (toString second)
                                  ")"))
     :evaluate       (fn [_ values]
                       (operation
                         (evaluate first values)
                         (evaluate second values)))
     :diff           d
     :arguments      [first second]
     :toStringSuffix (fn [_] (str "("
                                  (toStringSuffix first)
                                  " "
                                  (toStringSuffix second)
                                  " "
                                  opStr
                                  ")"))})
  )

(defn unary [opStr operation d]
  (fn [first]
    {:toString       (fn [_] (str "("
                                  opStr
                                  " "
                                  (toString first)
                                  ")"))
     :evaluate       (fn [_ values]
                       (operation
                         (evaluate first values)))
     :diff           d
     :arguments      [first second]
     :toStringSuffix (fn [_] (str "("
                                  (toStringSuffix first)
                                  " "
                                  opStr
                                  ")"))})
  )

(def Constant (valueConstructor
                (fn [expression _] (expression :arguments))
                (fn [_ _] (Constant (double 0)))))
(def E (Constant (Math/exp 1)))
(def Variable (valueConstructor
                (fn [expression values]
                  (get values ((comp clojure.string/lower-case first) (expression :arguments))))
                (fn [expression values]
                  (cond (= (expression :arguments) values)
                        (Constant (double 1))
                        :else (Constant (double 0))))))
(def Add (binary "+" +
                 (fn [expression values]
                   (Add
                     (diff (first (expression :arguments)) values)
                     (diff (second (expression :arguments)) values)))))
(def Subtract (binary "-" -
                      (fn [expression values]
                        (Subtract
                          (diff (first (expression :arguments)) values)
                          (diff (second (expression :arguments)) values)))))
(def Multiply (binary "*" *
                      (fn [expression values]
                        (Add
                          (Multiply (diff (first (expression :arguments)) values) (second (expression :arguments)))
                          (Multiply (first (expression :arguments)) (diff (second (expression :arguments)) values)))
                        )))
(def Divide (binary "/" #(/ (double %1) (double %2))
                    (fn [expression values]
                      (Divide
                        (Subtract
                          (Multiply (diff (first (expression :arguments)) values) (second (expression :arguments)))
                          (Multiply (first (expression :arguments)) (diff (second (expression :arguments)) values)))
                        (Multiply (second (expression :arguments)) (second (expression :arguments)))))
                    ))
(def Negate (unary "negate" -
                   (fn [expression values]
                     (Negate
                       (diff (first (expression :arguments)) values)))))
(def Log (binary "log" #(/ (Math/log (Math/abs %2)) (Math/log (Math/abs %1)))
                 (fn [expression values]
                   (cond
                     (= (first (expression :arguments)) E) (Divide
                                                             (diff (second (expression :arguments)) values)
                                                             (second (expression :arguments)))
                     :else (diff
                             (Divide
                               (Log E (second (expression :arguments)))
                               (Log E (first (expression :arguments))))
                             values)))))
(def Pow (binary "pow" #(Math/pow %1 %2)
                 (fn [expression values]
                   (Multiply
                     (Pow
                       (first (expression :arguments))
                       (second (expression :arguments)))
                     (Add
                       (Multiply
                         (second (expression :arguments))
                         (Divide
                           (diff (first (expression :arguments)) values)
                           (first (expression :arguments))))
                       (Multiply
                         (diff (second (expression :arguments)) values)
                         (Log E (first (expression :arguments)))))))))
(def BitAnd (binary "&"
                    #(Double/longBitsToDouble (bit-and (Double/doubleToLongBits %1) (Double/doubleToLongBits %2)))
                    #( %1 %2)))
(def BitOr (binary "|"
                   #(Double/longBitsToDouble (bit-or (Double/doubleToLongBits %1) (Double/doubleToLongBits %2)))
                   #( %1 %2)))
(def BitXor (binary "^"
                   #(Double/longBitsToDouble (bit-xor (Double/doubleToLongBits %1) (Double/doubleToLongBits %2)))
                   #( %1 %2)))
(def operationsObject {'+      Add
                       '-      Subtract
                       '*      Multiply
                       '/      Divide
                       'negate Negate
                       'pow    Pow
                       'log    Log
                       })

(defn parseObjectRecur [expression]
  (cond
    (symbol? expression) (Variable (str expression))
    (number? expression) (Constant (double expression))
    :else (apply (get operationsObject (first expression)) (mapv parseObjectRecur (rest expression)))))

(defn parseObject [expr] (parseObjectRecur (read-string expr)))

;---------------12---------------
(load-file "parser.clj")
(def operationsParser {"+"      Add
                       "-"      Subtract
                       "*"      Multiply
                       "/"      Divide
                       "negate" Negate
                       "&"      BitAnd
                       "|"      BitOr
                       "^"      BitXor
                       })

(def *digit (+char "0123456789"))
(def *all-chars (mapv char (range 32 128)))
(def *while-space (+ignore (+star (+char "\n\t\r "))))
(def *variable-char (+char "xyzXYZ"))
(def *br-open (+ignore (+char "(")))
(def *br-close (+ignore (+char ")")))
(def *number (+seq *while-space
                   (+opt (+char "-"))
                   (+plus *digit)
                   (+opt (+char "."))
                   (+opt (+plus *digit))))
(def *str-const (fn [[_1 _2 _3 _4]]
                  (Constant (read-string
                              (str _1 (apply str _2) _3 (apply str _4))))))
(defn *string [string] (apply +seq (reduce #(conj %1 (+char (str %2))) [] string)))

(def *variable
  (+map Variable (+str (+plus *variable-char))))

(def *const
  (+map *str-const
        *number))

(def *operation (+or
                  (+char "+-*/&|^")
                  (+str (*string "negate"))))

(defn *expr [parser] (+map (fn [expression]
                             (apply
                               (get operationsParser (str (peek expression)))
                               (first expression))) parser))

(def parse (+or (*expr (+seq *while-space
                             *br-open
                             *while-space
                             (+plus (delay parse))
                             *while-space
                             *operation
                             *while-space
                             *br-close
                             *while-space))
                (+map #(first %1) (+seq
                                    *while-space
                                    (+or *const *variable)
                                    *while-space))))

(def parseObjectSuffix (+parser parse))