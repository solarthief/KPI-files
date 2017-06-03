(defvar *db* nil)

(defun make-rec(surname name mid_name phone_number address)
	(list :surname surname :name name :mid_name mid_name :phone_number phone_number :address address))

(defun add-rec(rec)
	(push rec *db*))

(defun print-db()
	(format t "~{~{~a:~10t~a~%~}~%~}" *db*))

(defun prompt-read (prompt)
  (format *query-io* "~a: " prompt)
  (force-output *query-io*)
  (read-line *query-io*))

(defun inp-rec()
	(make-rec
		(prompt-read "Surname")
		(prompt-read "Name")
		(prompt-read "Middle name")
		(prompt-read "Phone number")
		(prompt-read "Address")))

(defun add-records()
	(loop (add-rec(inp-rec))
		(if (not (y-or-n-p "Another? [y/n]: ")) (return))))

(defun save-db(filename)
	(with-open-file (out filename
						:direction :output
						:if-exists :supersede)
		(with-standard-io-syntax (print *db* out))))

(defun load-db(filename)
	(with-open-file(in filename)
		(with-standard-io-syntax
			(setf *db* (read in)))))

(defun select(selector)
	(remove-if-not selector *db*))

(defun where (&key surname name mid_name phone_number address)
	#'(lambda (rec)
		(and
			(if surname (equal (getf rec :surname) surname) t)
			(if name (equal (getf rec :name) name) t)
			(if mid_name (equal (getf rec :mid_name) mid_name) t)
			(if phone_number (equal (getf rec :phone_number) phone_number) t)
			(if address (equal (getf rec :address) address) t)))) 

(defun update (selector &key surname name mid_name phone_number address)
	(setf *db* 
		(mapcar 
			#'(lambda (rec)
					(when (funcall selector rec)
						(if surname (setf (getf rec :surname) surname))
						(if name (setf(getf rec :name) name)) 
						(if mid_name (setf(getf rec :mid_name) mid_name)) 
						(if phone_number (setf(getf rec :phone_number) phone_number)) 
						(if address (setf(getf rec :address) address)))
					rec) *db*)))

(defun delete-rec (selector)
	(setf *db* (remove-if selector *db*)))

(defun is_masked (mask name)										
    (cond
	((and (NULL mask) (NULL name)) t)
    ((or (NULL mask) (NULL name )) nil )
	((equal (car mask) (car name)) (is_masked ( cdr mask ) ( cdr name )))
	((eq (car mask) #\*) 
			( if ( equal ( cadr mask ) ( cadr name ))
            (is_masked ( cdr mask ) ( cdr name )) 
	        (is_masked mask ( cdr name ))))
	( t nil )))

(defun masked(&key surname name mid_name)
#'(lambda (rec)
	(and
		(if surname (is_masked (coerce surname 'list) (coerce (getf rec :surname) 'list)) t)
		(if name (is_masked (coerce name 'list) (coerce (getf rec :name) 'list)) t) 
		(if mid_name (is_masked (coerce mid_name 'list) (coerce (getf rec :mid_name) 'list)) t) 
)))

(defun menu()
(loop
(let* ()
	(print "1. List all")
	(print "2. Add new contacts")
	(print "3. Delete contact")
	(print "4. List contacts by name mask")
	(print "5. Find by name")
	(print "6. Find by phone")
	(print "")
	(defvar ch nil)
	(setq ch (read))
	(cond 
		((eq ch 1) (print-db))
		((eq ch 2) (add-records))
		((eq ch 3) (delete-rec (where :surname (read-line))))
		((eq ch 4)
		(format t "~{~{~a:~10t~a~%~}~%~}" (select (masked :name (read-line)))))
		((eq ch 5) 
		(format t "~{~{~a:~10t~a~%~}~%~}" (select (where :surname (read-line)))))
		((eq ch 6) 
		(format t "~{~{~a:~10t~a~%~}~%~}" (select (where :phone_number (read-line)))))
		(t (return)))

)))

(menu)