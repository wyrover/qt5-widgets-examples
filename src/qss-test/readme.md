# qt5 下使用 cmake


## 生成 exe

```
add_executable(helloworld ${SOURCE_FILES} ${UI_HEADERS} ${QRCS})
```

## 生成库

```
set(CMAKE_AUTOMOC ON)
aux_source_directory(. QSLOG_SRC)
add_library(qslog STATIC ${QSLOG_SRC})
```