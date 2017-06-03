(defun rgr (i)
(cond
	((or (< i 0) (> i 20)) (print "Please, use numbers from 1 to 20"))
	((or (eql i 1)  (eql i 11)) 1)
	((< i 11) (* (rgr (- i 1)) (* (log i) 8 )))
	((< i 21) (* (rgr (- i 1)) (/ (log i) 8 )))
	(t (print "Error"))
))


(rgr 'r) 