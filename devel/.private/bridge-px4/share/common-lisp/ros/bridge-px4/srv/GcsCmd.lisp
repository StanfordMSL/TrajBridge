; Auto-generated. Do not edit!


(cl:in-package bridge-px4-srv)


;//! \htmlinclude GcsCmd-request.msg.html

(cl:defclass <GcsCmd-request> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:integer
    :initform 0)
   (trigger
    :reader trigger
    :initarg :trigger
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GcsCmd-request (<GcsCmd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GcsCmd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GcsCmd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bridge-px4-srv:<GcsCmd-request> is deprecated: use bridge-px4-srv:GcsCmd-request instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <GcsCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bridge-px4-srv:mode-val is deprecated.  Use bridge-px4-srv:mode instead.")
  (mode m))

(cl:ensure-generic-function 'trigger-val :lambda-list '(m))
(cl:defmethod trigger-val ((m <GcsCmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bridge-px4-srv:trigger-val is deprecated.  Use bridge-px4-srv:trigger instead.")
  (trigger m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GcsCmd-request>) ostream)
  "Serializes a message object of type '<GcsCmd-request>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'trigger) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GcsCmd-request>) istream)
  "Deserializes a message object of type '<GcsCmd-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:setf (cl:slot-value msg 'trigger) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GcsCmd-request>)))
  "Returns string type for a service object of type '<GcsCmd-request>"
  "bridge-px4/GcsCmdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GcsCmd-request)))
  "Returns string type for a service object of type 'GcsCmd-request"
  "bridge-px4/GcsCmdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GcsCmd-request>)))
  "Returns md5sum for a message object of type '<GcsCmd-request>"
  "036b31736abf2284d72b9d0bf32bb22a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GcsCmd-request)))
  "Returns md5sum for a message object of type 'GcsCmd-request"
  "036b31736abf2284d72b9d0bf32bb22a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GcsCmd-request>)))
  "Returns full string definition for message of type '<GcsCmd-request>"
  (cl:format cl:nil "int64 mode~%bool trigger~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GcsCmd-request)))
  "Returns full string definition for message of type 'GcsCmd-request"
  (cl:format cl:nil "int64 mode~%bool trigger~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GcsCmd-request>))
  (cl:+ 0
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GcsCmd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GcsCmd-request
    (cl:cons ':mode (mode msg))
    (cl:cons ':trigger (trigger msg))
))
;//! \htmlinclude GcsCmd-response.msg.html

(cl:defclass <GcsCmd-response> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:integer
    :initform 0)
   (pose_init
    :reader pose_init
    :initarg :pose_init
    :type (cl:vector cl:float)
   :initform (cl:make-array 13 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass GcsCmd-response (<GcsCmd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GcsCmd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GcsCmd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bridge-px4-srv:<GcsCmd-response> is deprecated: use bridge-px4-srv:GcsCmd-response instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <GcsCmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bridge-px4-srv:mode-val is deprecated.  Use bridge-px4-srv:mode instead.")
  (mode m))

(cl:ensure-generic-function 'pose_init-val :lambda-list '(m))
(cl:defmethod pose_init-val ((m <GcsCmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bridge-px4-srv:pose_init-val is deprecated.  Use bridge-px4-srv:pose_init instead.")
  (pose_init m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GcsCmd-response>) ostream)
  "Serializes a message object of type '<GcsCmd-response>"
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pose_init))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GcsCmd-response>) istream)
  "Deserializes a message object of type '<GcsCmd-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  (cl:setf (cl:slot-value msg 'pose_init) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'pose_init)))
    (cl:dotimes (i 13)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GcsCmd-response>)))
  "Returns string type for a service object of type '<GcsCmd-response>"
  "bridge-px4/GcsCmdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GcsCmd-response)))
  "Returns string type for a service object of type 'GcsCmd-response"
  "bridge-px4/GcsCmdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GcsCmd-response>)))
  "Returns md5sum for a message object of type '<GcsCmd-response>"
  "036b31736abf2284d72b9d0bf32bb22a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GcsCmd-response)))
  "Returns md5sum for a message object of type 'GcsCmd-response"
  "036b31736abf2284d72b9d0bf32bb22a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GcsCmd-response>)))
  "Returns full string definition for message of type '<GcsCmd-response>"
  (cl:format cl:nil "int64 mode~%float32[13] pose_init~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GcsCmd-response)))
  "Returns full string definition for message of type 'GcsCmd-response"
  (cl:format cl:nil "int64 mode~%float32[13] pose_init~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GcsCmd-response>))
  (cl:+ 0
     8
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pose_init) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GcsCmd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GcsCmd-response
    (cl:cons ':mode (mode msg))
    (cl:cons ':pose_init (pose_init msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GcsCmd)))
  'GcsCmd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GcsCmd)))
  'GcsCmd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GcsCmd)))
  "Returns string type for a service object of type '<GcsCmd>"
  "bridge-px4/GcsCmd")