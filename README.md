# Number-to-text converter
This simple program in C outputs the text representation of a number in either English or Kazakh, depending on the current system locale.

## Build
Run the following command to build the program:
```sh
$ make -f build/Makefile
```

## Usage
First, copy the built program to the `locale` directory:
```sh
$ cp number-to-text-converter locale/
```

Go to the `locale` directory:
```sh
$ cd locale/
```

Run the following command to get the output in English:
```sh
$ LC_ALL= LANGUAGE= ./number-to-text-converter <number>
```

or the following to get the output in Kazakh:
```sh
$ LC_ALL=kk_KZ.UTF-8 LANGUAGE=kk ./number-to-text-converter <number>
```

## License
This program is licensed under the MIT License. See the `LICENSE` file for details.
