
(cl:in-package :asdf)

(defsystem "bridge-px4-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GcsCmd" :depends-on ("_package_GcsCmd"))
    (:file "_package_GcsCmd" :depends-on ("_package"))
  ))