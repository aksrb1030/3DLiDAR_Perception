
(cl:in-package :asdf)

(defsystem "ouster_lidar-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
               :visualization_msgs-msg
)
  :components ((:file "_package")
    (:file "DetectedObject" :depends-on ("_package_DetectedObject"))
    (:file "_package_DetectedObject" :depends-on ("_package"))
    (:file "DetectedObjectArray" :depends-on ("_package_DetectedObjectArray"))
    (:file "_package_DetectedObjectArray" :depends-on ("_package"))
    (:file "MarkerClassification" :depends-on ("_package_MarkerClassification"))
    (:file "_package_MarkerClassification" :depends-on ("_package"))
    (:file "MarkerWithCloud" :depends-on ("_package_MarkerWithCloud"))
    (:file "_package_MarkerWithCloud" :depends-on ("_package"))
    (:file "MarkerWithCloudArray" :depends-on ("_package_MarkerWithCloudArray"))
    (:file "_package_MarkerWithCloudArray" :depends-on ("_package"))
  ))