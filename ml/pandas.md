# pandas

- read_csv

```python
pd.read_csv('girl.csv', sep='\t', header=第几行作为表头, names=[表头的名字列表],usecols=[使用的列],dtype=数据类型,na_values=[],skip_blank_lines=bool)
# na_values 参数可以配置哪些值需要处理成 NaN
# skip_blank_lines 默认为 True，表示过滤掉空行，如为 False 则解析为 NaN


```

* **converters**

```python
# 可以在读取的时候对列数据进行变换
pd.read_csv('girl.csv', sep="\t", converters={"id": lambda x: int(x) + 10})
```

