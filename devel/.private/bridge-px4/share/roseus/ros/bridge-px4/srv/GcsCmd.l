;; Auto-generated. Do not edit!


(when (boundp 'bridge-px4::GcsCmd)
  (if (not (find-package "BRIDGE-PX4"))
    (make-package "BRIDGE-PX4"))
  (shadow 'GcsCmd (find-package "BRIDGE-PX4")))
(unless (find-package "BRIDGE-PX4::GCSCMD")
  (make-package "BRIDGE-PX4::GCSCMD"))
(unless (find-package "BRIDGE-PX4::GCSCMDREQUEST")
  (make-package "BRIDGE-PX4::GCSCMDREQUEST"))
(unless (find-package "BRIDGE-PX4::GCSCMDRESPONSE")
  (make-package "BRIDGE-PX4::GCSCMDRESPONSE"))

(in-package "ROS")





(defclass bridge-px4::GcsCmdRequest
  :super ros::object
  :slots (_mode _trigger ))

(defmethod bridge-px4::GcsCmdRequest
  (:init
   (&key
    ((:mode __mode) 0)
    ((:trigger __trigger) nil)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _trigger __trigger)
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:trigger
   (&optional __trigger)
   (if __trigger (setq _trigger __trigger)) _trigger)
  (:serialization-length
   ()
   (+
    ;; int64 _mode
    8
    ;; bool _trigger
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _mode (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _mode) (= (length (_mode . bv)) 2)) ;; bignum
              (write-long (ash (elt (_mode . bv) 0) 0) s)
              (write-long (ash (elt (_mode . bv) 1) -1) s))
             ((and (class _mode) (= (length (_mode . bv)) 1)) ;; big1
              (write-long (elt (_mode . bv) 0) s)
              (write-long (if (>= _mode 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _mode s)(write-long (if (>= _mode 0) 0 #xffffffff) s)))
     ;; bool _trigger
       (if _trigger (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
      (setf _mode (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _mode (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; bool _trigger
     (setq _trigger (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass bridge-px4::GcsCmdResponse
  :super ros::object
  :slots (_mode _pose_init ))

(defmethod bridge-px4::GcsCmdResponse
  (:init
   (&key
    ((:mode __mode) 0)
    ((:pose_init __pose_init) (make-array 13 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _pose_init __pose_init)
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:pose_init
   (&optional __pose_init)
   (if __pose_init (setq _pose_init __pose_init)) _pose_init)
  (:serialization-length
   ()
   (+
    ;; int64 _mode
    8
    ;; float32[13] _pose_init
    (* 4    13)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _mode (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _mode) (= (length (_mode . bv)) 2)) ;; bignum
              (write-long (ash (elt (_mode . bv) 0) 0) s)
              (write-long (ash (elt (_mode . bv) 1) -1) s))
             ((and (class _mode) (= (length (_mode . bv)) 1)) ;; big1
              (write-long (elt (_mode . bv) 0) s)
              (write-long (if (>= _mode 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _mode s)(write-long (if (>= _mode 0) 0 #xffffffff) s)))
     ;; float32[13] _pose_init
     (dotimes (i 13)
       (sys::poke (elt _pose_init i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _mode
#+(or :alpha :irix6 :x86_64)
      (setf _mode (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _mode (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; float32[13] _pose_init
   (dotimes (i (length _pose_init))
     (setf (elt _pose_init i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(defclass bridge-px4::GcsCmd
  :super ros::object
  :slots ())

(setf (get bridge-px4::GcsCmd :md5sum-) "036b31736abf2284d72b9d0bf32bb22a")
(setf (get bridge-px4::GcsCmd :datatype-) "bridge-px4/GcsCmd")
(setf (get bridge-px4::GcsCmd :request) bridge-px4::GcsCmdRequest)
(setf (get bridge-px4::GcsCmd :response) bridge-px4::GcsCmdResponse)

(defmethod bridge-px4::GcsCmdRequest
  (:response () (instance bridge-px4::GcsCmdResponse :init)))

(setf (get bridge-px4::GcsCmdRequest :md5sum-) "036b31736abf2284d72b9d0bf32bb22a")
(setf (get bridge-px4::GcsCmdRequest :datatype-) "bridge-px4/GcsCmdRequest")
(setf (get bridge-px4::GcsCmdRequest :definition-)
      "int64 mode
bool trigger
---
int64 mode
float32[13] pose_init

")

(setf (get bridge-px4::GcsCmdResponse :md5sum-) "036b31736abf2284d72b9d0bf32bb22a")
(setf (get bridge-px4::GcsCmdResponse :datatype-) "bridge-px4/GcsCmdResponse")
(setf (get bridge-px4::GcsCmdResponse :definition-)
      "int64 mode
bool trigger
---
int64 mode
float32[13] pose_init

")



(provide :bridge-px4/GcsCmd "036b31736abf2284d72b9d0bf32bb22a")


