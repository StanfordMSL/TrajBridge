// Auto-generated. Do not edit!

// (in-package bridge-px4.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class GcsCmdRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mode = null;
      this.trigger = null;
    }
    else {
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('trigger')) {
        this.trigger = initObj.trigger
      }
      else {
        this.trigger = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GcsCmdRequest
    // Serialize message field [mode]
    bufferOffset = _serializer.int64(obj.mode, buffer, bufferOffset);
    // Serialize message field [trigger]
    bufferOffset = _serializer.bool(obj.trigger, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GcsCmdRequest
    let len;
    let data = new GcsCmdRequest(null);
    // Deserialize message field [mode]
    data.mode = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [trigger]
    data.trigger = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 9;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bridge-px4/GcsCmdRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '84198c51295025131dc178a2618fe32d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 mode
    bool trigger
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GcsCmdRequest(null);
    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.trigger !== undefined) {
      resolved.trigger = msg.trigger;
    }
    else {
      resolved.trigger = false
    }

    return resolved;
    }
};

class GcsCmdResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mode = null;
      this.pose_init = null;
    }
    else {
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('pose_init')) {
        this.pose_init = initObj.pose_init
      }
      else {
        this.pose_init = new Array(13).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GcsCmdResponse
    // Serialize message field [mode]
    bufferOffset = _serializer.int64(obj.mode, buffer, bufferOffset);
    // Check that the constant length array field [pose_init] has the right length
    if (obj.pose_init.length !== 13) {
      throw new Error('Unable to serialize array field pose_init - length must be 13')
    }
    // Serialize message field [pose_init]
    bufferOffset = _arraySerializer.float32(obj.pose_init, buffer, bufferOffset, 13);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GcsCmdResponse
    let len;
    let data = new GcsCmdResponse(null);
    // Deserialize message field [mode]
    data.mode = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [pose_init]
    data.pose_init = _arrayDeserializer.float32(buffer, bufferOffset, 13)
    return data;
  }

  static getMessageSize(object) {
    return 60;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bridge-px4/GcsCmdResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c3831fccdca0ab32888af6ef62cefaf7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 mode
    float32[13] pose_init
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GcsCmdResponse(null);
    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.pose_init !== undefined) {
      resolved.pose_init = msg.pose_init;
    }
    else {
      resolved.pose_init = new Array(13).fill(0)
    }

    return resolved;
    }
};

module.exports = {
  Request: GcsCmdRequest,
  Response: GcsCmdResponse,
  md5sum() { return '036b31736abf2284d72b9d0bf32bb22a'; },
  datatype() { return 'bridge-px4/GcsCmd'; }
};
