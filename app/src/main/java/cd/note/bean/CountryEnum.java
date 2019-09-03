package cd.note.bean;

/**
 * 作者：chenda
 * 时间：2019/9/3:15:41
 * 邮箱：
 * 说明：
 */
public enum CountryEnum {

    ONE(1,"齐"),TWO(2,"楚"),THREE(3,"燕"),FOUR(4,"赵"),FIVE(5,"魏"),SIX(6,"韩");  //6个对象

    private int code;
    private String country;

    CountryEnum(int code, String country) {
        this.code = code;
        this.country = country;
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public static CountryEnum forEach_CountryEnum(int code){
        CountryEnum[] countryEnums = CountryEnum.values();
        for (CountryEnum countryEnum : countryEnums){
            if(countryEnum.getCode()==code)
                return countryEnum;
        }
        return null;
    }

}
