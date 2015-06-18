;;; Copyright (c) 2013, Jan Winkler <winkler@cs.uni-bremen.de>
;;; All rights reserved.
;;; 
;;; Redistribution and use in source and binary forms, with or without
;;; modification, are permitted provided that the following conditions are met:
;;; 
;;;     * Redistributions of source code must retain the above copyright
;;;       notice, this list of conditions and the following disclaimer.
;;;     * Redistributions in binary form must reproduce the above copyright
;;;       notice, this list of conditions and the following disclaimer in the
;;;       documentation and/or other materials provided with the distribution.
;;;     * Neither the name of Willow Garage, Inc. nor the names of its
;;;       contributors may be used to endorse or promote products derived from
;;;       this software without specific prior written permission.
;;; 
;;; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;;; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;;; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;;; ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
;;; LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;;; CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;;; SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;;; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;;; CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;;; ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;;; POSSIBILITY OF SUCH DAMAGE.

(in-package :cl-user)

(desig-props:def-desig-package
 cram-moveit
 (:documentation "CRAM MoveIt! Interface")
 (:nicknames :moveit)
 (:use
  #:common-lisp
  #:cram-roslisp-common
  #:cram-reasoning
  #:cram-process-modules
  #:crs
  #:cut
  #:desig
  #:designators-ros
  #:roslisp
  #:cram-plan-failures)
  (:export
   ;; Functions
   check-state-validity
   clear-all-moveit-collision-objects
   get-planning-scene-info
   get-collision-matrix-entry
   set-collision-matrix-entry
   set-planning-scene-collision-matrix
   combine-collision-matrices
   move-link-pose
   plan-link-movement
   plan-link-movements
   init-moveit-bridge
   pose-distance
   add-collision-object
   remove-collision-object
   clear-collision-objects
   clear-collision-environment
   joint-states
   copy-physical-joint-states
   set-planning-robot-state
   register-collision-object
   unregister-collision-object
   named-collision-object
   attach-collision-object-to-link
   detach-collision-object-from-link
   get-joint-value
   set-collision-object-pose
   compute-fk
   compute-ik
   execute-trajectory
   merge-trajectories
   concatenate-trajectories
   ;; Conditions
   moveit-failure
   planning-failed
   invalid-motion-plan
   motion-plan-invalidated-by-environment-change
   control-failed
   unable-to-acquire-sensor-data
   timed-out
   preempted
   start-state-in-collision
   start-state-violates-path-constraints
   goal-in-collision
   goal-violates-path-constraints
   goal-constraints-violated
   invalid-group-name
   invalid-goal-constraints
   invalid-robot-state
   invalid-link-name
   invalid-object-name
   frame-transform-failure
   collision-checking-unavailable
   robot-state-stale
   sensor-info-stale
   no-ik-solution
   no-collision-shapes-defined
   pose-not-transformable-into-link
   without-collision-object
   without-collision-objects
   execute-trajectories
   ;; Display
   display-robot-state
   set-object-color)
  (:import-from cram-roslisp-common *tf2*)
  (:desig-properties #:shape #:dimensions #:box #:cylinder
                     #:sphere #:cone #:round #:name #:yellow
                     #:color))
