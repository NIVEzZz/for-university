def foo(file_name, split_element):
    with open(file_name) as f:
        file = f.readlines()
        ans = {}
        for i in range (6):
            st = file[i]
            if i != 5:
                st = st[:-1]
            if len(st) == 0:
                continue
            st_list = st.split(split_element)
            for x in range (len(st_list)):
                element = st_list[x]
                if (element.isdigit() or (element[0] == "-" and element[1:].isdigit())):
                    st_list[x] = int(element)
                if (element.replace('.','').isdigit() or (element[0] == "-" and element[1:].replace('.','').isdigit())):
                    st_list[x] = float (st_list[x])
            ans[i] = st_list
        return ans
print(foo("csv_20260206_08a514.txt",","))
