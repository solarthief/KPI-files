(defun F9 (lst n)
(cond ((null lst) nil)	
	  ((> n 0) (F9 (append (last lst) (butlast lst)) (1- n)))
	  ((eql n 0) (cons  (list (car lst) (cadr lst)) (F9 (cddr lst) n)))
	  (t (print "Error"))
))


(F9 '(a b c d e f g h) 2) 