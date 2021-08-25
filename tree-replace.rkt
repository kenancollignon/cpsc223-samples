; ** problem 7 ** (10 points)
; Write a procedure

; (tree-replace old new tree)

; that returns a copy of the given tree with each element that is
; equal to old replaced by new


; Examples:

;; (tree-replace 1 2 '(1 2 3 4 5)) => '(2 2 3 4 5)
;; (tree-replace 1 2 '((1) (1 (2)))) => '((2) (2 (2)))
;; (tree-replace 2 1 '((1) (1 (2)))) => '((1) (1 (1)))
;; (tree-replace 1 2 '((((((1))))))) => '((((((2))))))
;; (tree-replace '((1)) 2 '((((((1))))))) => '((((2))))
;; (tree-replace 'x 'y '(a b x y x a z)) => '(a b y y y a z)
;; (tree-replace 'q 'y '(a b x y x a z)) => '(a b x y x a z)

; ********************************************************
(define (tree-replace old new tree)
  (cond
   [(and (not (list? tree)) (equal? old tree)) new]
   [(and (list? tree) (equal? old tree)) new]
   [(not (list? tree)) tree]
   [(empty? tree) '()]
   [(cons (tree-replace old new (car tree)) (tree-replace old new (cdr tree)))]))