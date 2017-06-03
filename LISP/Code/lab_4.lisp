(defun rec-l (lst)
(cond ((null lst) nil)
		(t (cons  (list (car lst) (car (last lst)) (car lst)) (rec-l (cdr (butlast lst)))))))

(rec-l '(a b c d e f g h q w e))