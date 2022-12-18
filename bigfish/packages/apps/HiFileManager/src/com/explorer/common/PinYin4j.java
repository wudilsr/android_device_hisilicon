package com.explorer.common;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
public class PinYin4j {


    public PinYin4j(){
    }
    public List<Set<String>> getHanziSpellList(List<File> hanzi){
        List<Set<String>> listSet=new ArrayList<Set<String>>();
        for(int i=0;i<hanzi.size();i++){
            listSet.add(getPinyin(hanzi.get(i).getName().toString()));
        }
        return listSet;
    }
    public String makeStringByStringSet(Set<String> stringSet) {
        StringBuilder str = new StringBuilder();
        int i = 0;
        for (String s : stringSet) {
            if (i == stringSet.size() - 1) {
                str.append(s);
            } else {
                str.append(s + ",");
            }
            i++;
        }
        return str.toString().toLowerCase();
    }
    public Set<String> getPinyin(String src) {
            char[] srcChar;
            srcChar = src.toCharArray();
            String[][] temp = new String[src.length()][];
            for (int i = 0; i < srcChar.length; i++) {
                char c = srcChar[i];
                if (String.valueOf(c).matches("[\\u4E00-\\u9FA5]+")) {
                        String[] t = PinyinHelper.getUnformattedHanyuPinyinStringArray(c);
                        temp[i] = new String[t.length];
                        for(int j=0;j<t.length;j++){
                            temp[i][j]=t[j].substring(0,1);
                        }
                } else if (((int) c >= 65 && (int) c <= 90)
                        || ((int) c >= 97 && (int) c <= 122)||c>=48&&c<=57||c==42) {
                    temp[i] = new String[] { String.valueOf(srcChar[i]) };
                } else {
                    temp[i] = new String[] {""};
                }

            }
            String[] pingyinArray = paiLie(temp);
            return array2Set(pingyinArray);
    }

    private String[] paiLie(String[][] str){
        int max=1;
        for(int i=0;i<str.length;i++){
            max*=str[i].length;
        }
        String[] result=new String[max];
        for(int i = 0; i < max; i++){
                String s = "";
                int temp = 1;
                for(int j = 0; j < str.length; j++){
                    temp *= str[j].length;
                    s += str[j][i / (max / temp) % str[j].length];
                }
                result[i]=s;
        }

        return result;
    }

    public static <T extends Object> Set<T> array2Set(T[] tArray) {
        Set<T> tSet = new HashSet<T>(Arrays.asList(tArray));
        return tSet;
    }
}
