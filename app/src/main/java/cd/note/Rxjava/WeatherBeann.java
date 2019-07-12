package cd.note.Rxjava;

import java.util.List;

/**
 * 作者：chenda
 * 时间：2019/7/12:10:09
 * 邮箱：
 * 说明：
 */
public class WeatherBeann {


    /**
     * result : {"data":{"realtime":{"wind":{"windspeed":"7.0","direct":"西北风","power":"2级","offset":null},"time":"16:00:00","weather":{"humidity":"91","img":"8","info":"中雨","temperature":"11"},"dataUptime":1451894824,"date":"2016-01-04","city_code":"101200101","city_name":"武汉","week":1,"moon":"十一月廿五"},"life":{"date":"2016-1-4","info":{"kongtiao":["较少开启","您将感到很舒适，一般不需要开启空调。"],"yundong":["较不宜","有降水，推荐您在室内进行低强度运动；若坚持户外运动，须注意保暖，做好准备活动，携带雨具。"],"ziwaixian":["最弱","属弱紫外线辐射天气，无需特别防护。若长期在户外，建议涂擦SPF在8-12之间的防晒护肤品。"],"ganmao":["极易发","将有一次强降温过程，且空气湿度较大，极易发生感冒，请特别注意增加衣服保暖防寒。"],"xiche":["不宜","不宜洗车，未来24小时内有雨，如果在此期间洗车，雨水和路上的泥水可能会再次弄脏您的爱车。"],"wuran":["良","气象条件有利于空气污染物稀释、扩散和清除，可在室外正常活动。"],"chuanyi":["较冷","建议着厚外套加毛衣等服装。年老体弱者宜着大衣、呢外套加羊毛衫。"]}},"weather":[{"date":"2016-01-04","info":{"night":["7","小雨","6","无持续风向","微风","17:34"],"day":["7","小雨","13","无持续风向","微风","07:20"]},"week":"一","nongli":"十一月廿五"},{"date":"2016-01-05","info":{"dawn":["7","小雨","6","无持续风向","微风","17:34"],"night":["2","阴","4","无持续风向","微风","17:35"],"day":["7","小雨","9","无持续风向","微风","07:20"]},"week":"二","nongli":"十一月廿六"},{"date":"2016-01-06","info":{"dawn":["2","阴","4","无持续风向","微风","17:35"],"night":["2","阴","4","无持续风向","微风","17:36"],"day":["0","晴","10","无持续风向","微风","07:20"]},"week":"三","nongli":"十一月廿七"},{"date":"2016-01-07","info":{"dawn":["2","阴","4","无持续风向","微风","17:36"],"night":["1","多云","0","无持续风向","微风","17:36"],"day":["7","小雨","10","无持续风向","微风","07:20"]},"week":"四","nongli":"十一月廿八"},{"date":"2016-01-08","info":{"dawn":["1","多云","0","无持续风向","微风","17:36"],"night":["1","多云","1","无持续风向","微风","17:37"],"day":["1","多云","10","无持续风向","微风","07:20"]},"week":"五","nongli":"十一月廿九"},{"date":"2016-01-09","info":{"night":["1","多云","2","","微风","19:30"],"day":["1","多云","11","","微风","07:30"]},"week":"六","nongli":"十一月三十"},{"date":"2016-01-10","info":{"night":["3","阵雨","2","东北风","微风","19:30"],"day":["3","阵雨","10","东北风","微风","07:30"]},"week":"日","nongli":"十二月初一"}],"pm25":{"key":"","show_desc":0,"pm25":{"curPm":"255","pm25":"227","pm10":"255","level":5,"quality":"重度污染","des":"老年人和心脏病、肺病患者应停留在室内，停止户外活动，一般人群减少户外运动。"},"dateTime":"2016年01月04日16时","cityName":"武汉"},"date":null,"isForeign":0}}
     * error_code : 0
     * reason : Succes
     */

    private ResultBean result;
    private int error_code;
    private String reason;

    public ResultBean getResult() {
        return result;
    }

    public void setResult(ResultBean result) {
        this.result = result;
    }

    public int getError_code() {
        return error_code;
    }

    public void setError_code(int error_code) {
        this.error_code = error_code;
    }

    public String getReason() {
        return reason;
    }

    public void setReason(String reason) {
        this.reason = reason;
    }

    public static class ResultBean {
        /**
         * data : {"realtime":{"wind":{"windspeed":"7.0","direct":"西北风","power":"2级","offset":null},"time":"16:00:00","weather":{"humidity":"91","img":"8","info":"中雨","temperature":"11"},"dataUptime":1451894824,"date":"2016-01-04","city_code":"101200101","city_name":"武汉","week":1,"moon":"十一月廿五"},"life":{"date":"2016-1-4","info":{"kongtiao":["较少开启","您将感到很舒适，一般不需要开启空调。"],"yundong":["较不宜","有降水，推荐您在室内进行低强度运动；若坚持户外运动，须注意保暖，做好准备活动，携带雨具。"],"ziwaixian":["最弱","属弱紫外线辐射天气，无需特别防护。若长期在户外，建议涂擦SPF在8-12之间的防晒护肤品。"],"ganmao":["极易发","将有一次强降温过程，且空气湿度较大，极易发生感冒，请特别注意增加衣服保暖防寒。"],"xiche":["不宜","不宜洗车，未来24小时内有雨，如果在此期间洗车，雨水和路上的泥水可能会再次弄脏您的爱车。"],"wuran":["良","气象条件有利于空气污染物稀释、扩散和清除，可在室外正常活动。"],"chuanyi":["较冷","建议着厚外套加毛衣等服装。年老体弱者宜着大衣、呢外套加羊毛衫。"]}},"weather":[{"date":"2016-01-04","info":{"night":["7","小雨","6","无持续风向","微风","17:34"],"day":["7","小雨","13","无持续风向","微风","07:20"]},"week":"一","nongli":"十一月廿五"},{"date":"2016-01-05","info":{"dawn":["7","小雨","6","无持续风向","微风","17:34"],"night":["2","阴","4","无持续风向","微风","17:35"],"day":["7","小雨","9","无持续风向","微风","07:20"]},"week":"二","nongli":"十一月廿六"},{"date":"2016-01-06","info":{"dawn":["2","阴","4","无持续风向","微风","17:35"],"night":["2","阴","4","无持续风向","微风","17:36"],"day":["0","晴","10","无持续风向","微风","07:20"]},"week":"三","nongli":"十一月廿七"},{"date":"2016-01-07","info":{"dawn":["2","阴","4","无持续风向","微风","17:36"],"night":["1","多云","0","无持续风向","微风","17:36"],"day":["7","小雨","10","无持续风向","微风","07:20"]},"week":"四","nongli":"十一月廿八"},{"date":"2016-01-08","info":{"dawn":["1","多云","0","无持续风向","微风","17:36"],"night":["1","多云","1","无持续风向","微风","17:37"],"day":["1","多云","10","无持续风向","微风","07:20"]},"week":"五","nongli":"十一月廿九"},{"date":"2016-01-09","info":{"night":["1","多云","2","","微风","19:30"],"day":["1","多云","11","","微风","07:30"]},"week":"六","nongli":"十一月三十"},{"date":"2016-01-10","info":{"night":["3","阵雨","2","东北风","微风","19:30"],"day":["3","阵雨","10","东北风","微风","07:30"]},"week":"日","nongli":"十二月初一"}],"pm25":{"key":"","show_desc":0,"pm25":{"curPm":"255","pm25":"227","pm10":"255","level":5,"quality":"重度污染","des":"老年人和心脏病、肺病患者应停留在室内，停止户外活动，一般人群减少户外运动。"},"dateTime":"2016年01月04日16时","cityName":"武汉"},"date":null,"isForeign":0}
         */

        private DataBean data;

        public DataBean getData() {
            return data;
        }

        public void setData(DataBean data) {
            this.data = data;
        }

        public static class DataBean {
            /**
             * realtime : {"wind":{"windspeed":"7.0","direct":"西北风","power":"2级","offset":null},"time":"16:00:00","weather":{"humidity":"91","img":"8","info":"中雨","temperature":"11"},"dataUptime":1451894824,"date":"2016-01-04","city_code":"101200101","city_name":"武汉","week":1,"moon":"十一月廿五"}
             * life : {"date":"2016-1-4","info":{"kongtiao":["较少开启","您将感到很舒适，一般不需要开启空调。"],"yundong":["较不宜","有降水，推荐您在室内进行低强度运动；若坚持户外运动，须注意保暖，做好准备活动，携带雨具。"],"ziwaixian":["最弱","属弱紫外线辐射天气，无需特别防护。若长期在户外，建议涂擦SPF在8-12之间的防晒护肤品。"],"ganmao":["极易发","将有一次强降温过程，且空气湿度较大，极易发生感冒，请特别注意增加衣服保暖防寒。"],"xiche":["不宜","不宜洗车，未来24小时内有雨，如果在此期间洗车，雨水和路上的泥水可能会再次弄脏您的爱车。"],"wuran":["良","气象条件有利于空气污染物稀释、扩散和清除，可在室外正常活动。"],"chuanyi":["较冷","建议着厚外套加毛衣等服装。年老体弱者宜着大衣、呢外套加羊毛衫。"]}}
             * weather : [{"date":"2016-01-04","info":{"night":["7","小雨","6","无持续风向","微风","17:34"],"day":["7","小雨","13","无持续风向","微风","07:20"]},"week":"一","nongli":"十一月廿五"},{"date":"2016-01-05","info":{"dawn":["7","小雨","6","无持续风向","微风","17:34"],"night":["2","阴","4","无持续风向","微风","17:35"],"day":["7","小雨","9","无持续风向","微风","07:20"]},"week":"二","nongli":"十一月廿六"},{"date":"2016-01-06","info":{"dawn":["2","阴","4","无持续风向","微风","17:35"],"night":["2","阴","4","无持续风向","微风","17:36"],"day":["0","晴","10","无持续风向","微风","07:20"]},"week":"三","nongli":"十一月廿七"},{"date":"2016-01-07","info":{"dawn":["2","阴","4","无持续风向","微风","17:36"],"night":["1","多云","0","无持续风向","微风","17:36"],"day":["7","小雨","10","无持续风向","微风","07:20"]},"week":"四","nongli":"十一月廿八"},{"date":"2016-01-08","info":{"dawn":["1","多云","0","无持续风向","微风","17:36"],"night":["1","多云","1","无持续风向","微风","17:37"],"day":["1","多云","10","无持续风向","微风","07:20"]},"week":"五","nongli":"十一月廿九"},{"date":"2016-01-09","info":{"night":["1","多云","2","","微风","19:30"],"day":["1","多云","11","","微风","07:30"]},"week":"六","nongli":"十一月三十"},{"date":"2016-01-10","info":{"night":["3","阵雨","2","东北风","微风","19:30"],"day":["3","阵雨","10","东北风","微风","07:30"]},"week":"日","nongli":"十二月初一"}]
             * pm25 : {"key":"","show_desc":0,"pm25":{"curPm":"255","pm25":"227","pm10":"255","level":5,"quality":"重度污染","des":"老年人和心脏病、肺病患者应停留在室内，停止户外活动，一般人群减少户外运动。"},"dateTime":"2016年01月04日16时","cityName":"武汉"}
             * date : null
             * isForeign : 0
             */

            private RealtimeBean realtime;
            private LifeBean life;
            private Pm25BeanX pm25;
            private Object date;
            private int isForeign;
            private List<WeatherBeanX> weather;

            public RealtimeBean getRealtime() {
                return realtime;
            }

            public void setRealtime(RealtimeBean realtime) {
                this.realtime = realtime;
            }

            public LifeBean getLife() {
                return life;
            }

            public void setLife(LifeBean life) {
                this.life = life;
            }

            public Pm25BeanX getPm25() {
                return pm25;
            }

            public void setPm25(Pm25BeanX pm25) {
                this.pm25 = pm25;
            }

            public Object getDate() {
                return date;
            }

            public void setDate(Object date) {
                this.date = date;
            }

            public int getIsForeign() {
                return isForeign;
            }

            public void setIsForeign(int isForeign) {
                this.isForeign = isForeign;
            }

            public List<WeatherBeanX> getWeather() {
                return weather;
            }

            public void setWeather(List<WeatherBeanX> weather) {
                this.weather = weather;
            }

            public static class RealtimeBean {
                /**
                 * wind : {"windspeed":"7.0","direct":"西北风","power":"2级","offset":null}
                 * time : 16:00:00
                 * weather : {"humidity":"91","img":"8","info":"中雨","temperature":"11"}
                 * dataUptime : 1451894824
                 * date : 2016-01-04
                 * city_code : 101200101
                 * city_name : 武汉
                 * week : 1
                 * moon : 十一月廿五
                 */

                private WindBean wind;
                private String time;
                private WeatherBean weather;
                private int dataUptime;
                private String date;
                private String city_code;
                private String city_name;
                private int week;
                private String moon;

                public WindBean getWind() {
                    return wind;
                }

                public void setWind(WindBean wind) {
                    this.wind = wind;
                }

                public String getTime() {
                    return time;
                }

                public void setTime(String time) {
                    this.time = time;
                }

                public WeatherBean getWeather() {
                    return weather;
                }

                public void setWeather(WeatherBean weather) {
                    this.weather = weather;
                }

                public int getDataUptime() {
                    return dataUptime;
                }

                public void setDataUptime(int dataUptime) {
                    this.dataUptime = dataUptime;
                }

                public String getDate() {
                    return date;
                }

                public void setDate(String date) {
                    this.date = date;
                }

                public String getCity_code() {
                    return city_code;
                }

                public void setCity_code(String city_code) {
                    this.city_code = city_code;
                }

                public String getCity_name() {
                    return city_name;
                }

                public void setCity_name(String city_name) {
                    this.city_name = city_name;
                }

                public int getWeek() {
                    return week;
                }

                public void setWeek(int week) {
                    this.week = week;
                }

                public String getMoon() {
                    return moon;
                }

                public void setMoon(String moon) {
                    this.moon = moon;
                }

                public static class WindBean {
                    /**
                     * windspeed : 7.0
                     * direct : 西北风
                     * power : 2级
                     * offset : null
                     */

                    private String windspeed;
                    private String direct;
                    private String power;
                    private Object offset;

                    public String getWindspeed() {
                        return windspeed;
                    }

                    public void setWindspeed(String windspeed) {
                        this.windspeed = windspeed;
                    }

                    public String getDirect() {
                        return direct;
                    }

                    public void setDirect(String direct) {
                        this.direct = direct;
                    }

                    public String getPower() {
                        return power;
                    }

                    public void setPower(String power) {
                        this.power = power;
                    }

                    public Object getOffset() {
                        return offset;
                    }

                    public void setOffset(Object offset) {
                        this.offset = offset;
                    }
                }

                public static class WeatherBean {
                    /**
                     * humidity : 91
                     * img : 8
                     * info : 中雨
                     * temperature : 11
                     */

                    private String humidity;
                    private String img;
                    private String info;
                    private String temperature;

                    public String getHumidity() {
                        return humidity;
                    }

                    public void setHumidity(String humidity) {
                        this.humidity = humidity;
                    }

                    public String getImg() {
                        return img;
                    }

                    public void setImg(String img) {
                        this.img = img;
                    }

                    public String getInfo() {
                        return info;
                    }

                    public void setInfo(String info) {
                        this.info = info;
                    }

                    public String getTemperature() {
                        return temperature;
                    }

                    public void setTemperature(String temperature) {
                        this.temperature = temperature;
                    }
                }
            }

            public static class LifeBean {
                /**
                 * date : 2016-1-4
                 * info : {"kongtiao":["较少开启","您将感到很舒适，一般不需要开启空调。"],"yundong":["较不宜","有降水，推荐您在室内进行低强度运动；若坚持户外运动，须注意保暖，做好准备活动，携带雨具。"],"ziwaixian":["最弱","属弱紫外线辐射天气，无需特别防护。若长期在户外，建议涂擦SPF在8-12之间的防晒护肤品。"],"ganmao":["极易发","将有一次强降温过程，且空气湿度较大，极易发生感冒，请特别注意增加衣服保暖防寒。"],"xiche":["不宜","不宜洗车，未来24小时内有雨，如果在此期间洗车，雨水和路上的泥水可能会再次弄脏您的爱车。"],"wuran":["良","气象条件有利于空气污染物稀释、扩散和清除，可在室外正常活动。"],"chuanyi":["较冷","建议着厚外套加毛衣等服装。年老体弱者宜着大衣、呢外套加羊毛衫。"]}
                 */

                private String date;
                private InfoBean info;

                public String getDate() {
                    return date;
                }

                public void setDate(String date) {
                    this.date = date;
                }

                public InfoBean getInfo() {
                    return info;
                }

                public void setInfo(InfoBean info) {
                    this.info = info;
                }

                public static class InfoBean {
                    private List<String> kongtiao;
                    private List<String> yundong;
                    private List<String> ziwaixian;
                    private List<String> ganmao;
                    private List<String> xiche;
                    private List<String> wuran;
                    private List<String> chuanyi;

                    public List<String> getKongtiao() {
                        return kongtiao;
                    }

                    public void setKongtiao(List<String> kongtiao) {
                        this.kongtiao = kongtiao;
                    }

                    public List<String> getYundong() {
                        return yundong;
                    }

                    public void setYundong(List<String> yundong) {
                        this.yundong = yundong;
                    }

                    public List<String> getZiwaixian() {
                        return ziwaixian;
                    }

                    public void setZiwaixian(List<String> ziwaixian) {
                        this.ziwaixian = ziwaixian;
                    }

                    public List<String> getGanmao() {
                        return ganmao;
                    }

                    public void setGanmao(List<String> ganmao) {
                        this.ganmao = ganmao;
                    }

                    public List<String> getXiche() {
                        return xiche;
                    }

                    public void setXiche(List<String> xiche) {
                        this.xiche = xiche;
                    }

                    public List<String> getWuran() {
                        return wuran;
                    }

                    public void setWuran(List<String> wuran) {
                        this.wuran = wuran;
                    }

                    public List<String> getChuanyi() {
                        return chuanyi;
                    }

                    public void setChuanyi(List<String> chuanyi) {
                        this.chuanyi = chuanyi;
                    }
                }
            }

            public static class Pm25BeanX {
                /**
                 * key :
                 * show_desc : 0
                 * pm25 : {"curPm":"255","pm25":"227","pm10":"255","level":5,"quality":"重度污染","des":"老年人和心脏病、肺病患者应停留在室内，停止户外活动，一般人群减少户外运动。"}
                 * dateTime : 2016年01月04日16时
                 * cityName : 武汉
                 */

                private String key;
                private int show_desc;
                private Pm25Bean pm25;
                private String dateTime;
                private String cityName;

                public String getKey() {
                    return key;
                }

                public void setKey(String key) {
                    this.key = key;
                }

                public int getShow_desc() {
                    return show_desc;
                }

                public void setShow_desc(int show_desc) {
                    this.show_desc = show_desc;
                }

                public Pm25Bean getPm25() {
                    return pm25;
                }

                public void setPm25(Pm25Bean pm25) {
                    this.pm25 = pm25;
                }

                public String getDateTime() {
                    return dateTime;
                }

                public void setDateTime(String dateTime) {
                    this.dateTime = dateTime;
                }

                public String getCityName() {
                    return cityName;
                }

                public void setCityName(String cityName) {
                    this.cityName = cityName;
                }

                public static class Pm25Bean {
                    /**
                     * curPm : 255
                     * pm25 : 227
                     * pm10 : 255
                     * level : 5
                     * quality : 重度污染
                     * des : 老年人和心脏病、肺病患者应停留在室内，停止户外活动，一般人群减少户外运动。
                     */

                    private String curPm;
                    private String pm25;
                    private String pm10;
                    private int level;
                    private String quality;
                    private String des;

                    public String getCurPm() {
                        return curPm;
                    }

                    public void setCurPm(String curPm) {
                        this.curPm = curPm;
                    }

                    public String getPm25() {
                        return pm25;
                    }

                    public void setPm25(String pm25) {
                        this.pm25 = pm25;
                    }

                    public String getPm10() {
                        return pm10;
                    }

                    public void setPm10(String pm10) {
                        this.pm10 = pm10;
                    }

                    public int getLevel() {
                        return level;
                    }

                    public void setLevel(int level) {
                        this.level = level;
                    }

                    public String getQuality() {
                        return quality;
                    }

                    public void setQuality(String quality) {
                        this.quality = quality;
                    }

                    public String getDes() {
                        return des;
                    }

                    public void setDes(String des) {
                        this.des = des;
                    }
                }
            }

            public static class WeatherBeanX {
                /**
                 * date : 2016-01-04
                 * info : {"night":["7","小雨","6","无持续风向","微风","17:34"],"day":["7","小雨","13","无持续风向","微风","07:20"]}
                 * week : 一
                 * nongli : 十一月廿五
                 */

                private String date;
                private InfoBeanX info;
                private String week;
                private String nongli;

                public String getDate() {
                    return date;
                }

                public void setDate(String date) {
                    this.date = date;
                }

                public InfoBeanX getInfo() {
                    return info;
                }

                public void setInfo(InfoBeanX info) {
                    this.info = info;
                }

                public String getWeek() {
                    return week;
                }

                public void setWeek(String week) {
                    this.week = week;
                }

                public String getNongli() {
                    return nongli;
                }

                public void setNongli(String nongli) {
                    this.nongli = nongli;
                }

                public static class InfoBeanX {
                    private List<String> night;
                    private List<String> day;

                    public List<String> getNight() {
                        return night;
                    }

                    public void setNight(List<String> night) {
                        this.night = night;
                    }

                    public List<String> getDay() {
                        return day;
                    }

                    public void setDay(List<String> day) {
                        this.day = day;
                    }
                }
            }
        }
    }
}
