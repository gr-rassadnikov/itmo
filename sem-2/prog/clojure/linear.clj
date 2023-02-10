(defn vectorOperation [operation]
  (fn [first second] (mapv operation first second)))
(def v+ (vectorOperation +))
(def v- (vectorOperation -))
(def v* (vectorOperation *))
(def vd (vectorOperation /))
(defn scalar [first second]
  (apply + (mapv * first second)))
(defn vect [first second] (vector
                            (- (* (first 1) (second 2)) (* (second 1) (first 2)))
                            (- (* (second 0) (first 2)) (* (first 0) (second 2)))
                            (- (* (first 0) (second 1)) (* (second 0) (first 1)))))
(defn v*s [vec scal]
  ((fn [vec] (mapv (partial * scal) vec)) vec))


(def m+ (vectorOperation v+))
(def m- (vectorOperation v-))
(def m* (vectorOperation v*))
(def md (vectorOperation vd))
(defn m*s [mat scal]
  (mapv
    (fn [mat] (mapv (partial * scal) mat)) mat))
(defn m*v [mat vec]
  (mapv (partial scalar vec) mat))

(defn transpose [mat]
  (apply mapv vector mat))

(defn m*m [matFirst matSecond]
  (mapv (partial m*v
                 (transpose matSecond)) matFirst))
(defn sOperation [operation]
  (fn [first second] (cond
                       (number? first) (operation first second)
                       :else (mapv (sOperation operation) first second)
                       )))
(def s+ (sOperation +))
(def s- (sOperation -))
(def s* (sOperation *))
(def sd (sOperation /))
