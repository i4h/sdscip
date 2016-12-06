# Installation

## Installing Dependencies

SD-SCIP has several dependencies that need to be running on your system in order to compile SD-SCIP:

### SCIP

Go to [http://scip.zib.de] to download and install SCIP. 
SD-SCIP expects to find a link to your scip installation in the `lib` directory.To create a link, go to your sdscip directory and run
````
$> cd lib
$> ln -s ~/repos/sd-scip/scip-suite/scip/ scip
````


### SDO Tools

The SDO Tools are a set of tools used by SD-SCIP that are also available on github. They were developed by Robert Gottwald in coopartion with the author of SD-SCIP. SD-SCIP depends on the following components of the SDO Tools:

- __libsdo__ A library for parsing SDOs in Vensim format (github)[https://github.com/rgottwald/libsdo].
- __spline__ A library to represent table functions appearing in SDOs as linear or cubic splines (github)[https://github.com/rgottwald/spline].
- __ccplsq__ A least-squares library used by spline to compute spline approximations (github)[https://github.com/rgottwald/cpplsq]

SD-SCIP comes with a script that installs these libraries for you. Once you have cloned the SD-SCIP repository, change into its directory and run:
````
$> cd sdotools
$> ./get_sdotools
````
This will download and build the required libraries, and install them to ~/lib/sdotools. This is the path for sdotools used in the Makefile that comes with SD-SCIP.


## Compiling SD-SCIP	 

After installing the dependencies, you can compile SD-SCIP. Note that SCIP needs to be compiled with the same make flags you use for compiling SD-SCIP. For instance, in order to use IPOPT, SCIP and SD-SCIP both need to be compiled by calling
````
make IPOPT=true ...
````
# Running Tests

## Unittests
SD-SCIP comes with a set of unit tests. To run the tests, compile the `unittest` make target. This will automatically run all tests.

## Tests
Some System Dynamics Optimization Problems can be found in the problems directory. To run the tests, call the run_tests.sh script in the sdscip directory.

