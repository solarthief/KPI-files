(defparameter *w-list* '(0.01 0.1 10 100))

(defun parallel (resist1 resist2)
(/ (* resist1 resist2) (+ resist1 resist2)))

(defun series (resist1 resist2)
(+ resist1 resist2))

(defun resistance(el w)
(cond 
	((equalp (car el) 'r) (cadr el))
	((equalp (car el) 'l) (* #c(0.0 1.0) w (cadr el)))
	((equalp (car el) 'c) (/ 1 (* #c(0.0 1.0) w (cadr el))))
	(t (print "Wrong element")))
)

(defun my-circuit(w)
(series (resistance '(L 20) w)
		(parallel (resistance '(R 25) w)
				  (resistance '(C 0.000002) w))))


(defun test(w-list)
(cond 
	((null w-list) nil)
	(t 
		(dolist (w w-list)
		(format t "~%~%Circuit`s resistance with w=~F is equal to ~w" 
		w (my-circuit w))))
	))

(test *w-list*)