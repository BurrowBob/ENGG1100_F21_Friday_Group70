# ENGG1100_F21_Friday_Group70
This project contains a basic encryption/decryption utility written in C called cryptoMagic.
crytoMagic takes two inputs from the command line: a swich to encrypt or decrypt, and a file name.
crytoMagic will encrypt ASCII files given the commands -encrypt [filename], or simply [filename].
it will also decrypt .cpr files given the commands -decrypt [filename].If no switch is specified,
then cryptoMagic will assume that the user wants to encrypt their file. If no file extension is
specified during encryption, an extension of .txt will be assumed, while an extension of .crp
will be assumed for decryption.
