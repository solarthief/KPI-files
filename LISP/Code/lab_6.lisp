(defun m-gcd (a b)
(cond 
	((eql a b) a)
	((< a b) (m-gcd a (- b a)))
	(t (m-gcd b (- a b)))
))


(defun coprimep (a b)
	(cond	((or (not (numberp a)) (not (numberp b)) 
			 (< a 0) (< b 0)) (print "Invalid numbers")) 
			(t (eql 1 (m-gcd a b)))
))

(coprimep 10 48)