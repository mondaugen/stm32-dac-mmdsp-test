.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.align 2 /* align to 4 byte boundary */
SoundFileData:
    .incbin "data/win-low.raw"
