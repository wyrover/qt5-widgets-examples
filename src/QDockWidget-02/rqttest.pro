QT += core gui widgets svg

CONFIG += qt debug

TEMPLATE = app
HEADERS = rqttest.h 
SOURCES = rqttest.cpp \
                main.cpp

R_HOME = $$system(R RHOME)

RCPPFLAGS = $$system($$R_HOME/bin/R CMD config --cppflags)
RLDFLAGS = $$system($$R_HOME/bin/R CMD config --ldflags)
RBLAS = $$system($$R_HOME/bin/R CMD config BLAS_LIBS)
RLAPACK = $$system($$R_HOME/bin/R CMD config LAPACK_LIBS)

RRPATH =-Wl,-rpath,$$R_HOME/lib

RCPPINCL =$$system($$R_HOME/bin/Rscript -e \"Rcpp:::CxxFlags\(\)\")

RINSIDEINCL = $$system($$R_HOME/bin/Rscript -e \"RInside:::CxxFlags\(\)\")
RINSIDELIBS = $$system($$R_HOME/bin/Rscript -e \"RInside:::LdFlags\(\)\")

QMAKE_CXXFLAGS +=$$RCPPWARNING $$RCPPFLAGS $$RCPPINCL $$RINSIDEINCL
QMAKE_LIBS += $$RLDFLAGS $$RBLAS $$RLAPACK $$RINSIDELIBS $$RCPPLIBS

QMAKE_CLEAN +=rqttest \
Makefile
