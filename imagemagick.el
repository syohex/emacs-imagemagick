;;; imagemagick.el --- ImageMagick++ binding of Emacs Lisp -*- lexical-binding: t -*-

;; Copyright (C) 2020 by Shohei YOSHIDA

;; Author: Syohei YOSHIDA <syohex@gmail.com>
;; URL: https://github.com/syohex/emacs-imagemagick
;; Package-Requires: ((emacs "26.3"))
;; Version: 0.01

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

;;; Commentary:

;;; Code:

(require 'cl-lib)
(require 'imagemagick-core)

(defvar imagemagick--initialized nil)

;;;###autoload
(defun imagemagick-init ()
  "Initialize imagemagick module"
  (unless imagemagick--initialized
    (imagemagick-core-init)
    (setq imagemagick--initialized t)))

(defun imagemagick-scale (src dest geo)
  "Resize `src' image by `geo' and write it to `dest'.
`geo' is ImageMagick geometry format like 200%, 1000x1000"
  (unless (file-exists-p src)
    (user-error "Source file %s does not exists" src))
  (imagemagick-core-scale src dest ratio))

(cl-defun imagemagick-blur (src dest &optional (radius 1.0) (sigma 1.0))
  "Blur `src' image by radius and sigma and write it to `dest'"
  (unless (file-exists-p src)
    (user-error "Source file %s does not exists" src))
  (imagemagick-core-blur src dest radius sigma))

(defun imagemagick-size (src)
  "Get image size as cons list (rows . columns)"
  (unless (file-exists-p src)
    (user-error "Source file %s does not exists" src))
  (imagemagick-core-size src))

(provide 'imagemagick)

;;; sqlite3.el ends here
