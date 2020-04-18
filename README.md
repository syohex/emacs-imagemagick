# imagemagick.el

Emacs binding of [ImageMagick++](https://imagemagick.org/index.php) inspired by [mruby-mrmagick](https://github.com/kjunichi/mruby-mrmagick)

## Example

### Scale

```lisp
(imagemagick-init)
(imagemagick-scale "image/Lenna.png" "image/half.png" "50%")
(imagemagick-scale "image/Lenna.png" "image/twice.png" "200%")
```

|original                |half                   |twice                    |
|------------------------|-----------------------|-------------------------|
|![orig](image/Lenna.png)|![half](image/half.png)|![twice](image/twice.png)|

### Blur

```lisp
(imagemagick-init)
(imagemagick-blur "image/Lenna.png" "image/blur.png" 0.0 8.0)
```

|original                |blur                   |
|------------------------|-----------------------|
|![orig](image/Lenna.png)|![blur](image/blur.png)|

### Get size

```lisp
(imagemagick-init)
(imagemagick-size "image/Lenna.png")
;; => (512 . 512)
```
