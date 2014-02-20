var Template=module.exports={   
    parse: function(tmpstr, data){
        var re = /#\{([\w\.]*)\}/g;
        //re.test(tmpstr) 性能改善不是很大
        return tmpstr.replace(re, function(a, b){
            return Template.attr(data, b);
        });
    },
    /**
     * 取出对象的值
     * 对于取对像的子值十分有用
     * @param {Object} obj 某个对像
     * @param {Object} name 值的名称，使用"."分隔
     *
     * 对像user的属性user.school.master.name="test"
     * arrt(user,"school.master.name")=="test"
     * 
     * user.school.master=[{"name":"test"},{"name":"test2"}]
     * arrt(user,"school.master.0.name")=="test"
     */
    attr: function(obj, name,v){
        if(typeof v=="undefined")
            return this.getAttr(obj,name);
        else
            return this.setAttr(obj,name,v);
    },
    getAttr: function(obj, name){
        var r, t;
        if (name.indexOf(".") > -1) {
            t = name.split(".");
            r = obj[t[0]];
            for (var i = 1; i < t.length; i++) {
                r = r[t[i]];
            }
        } else {
            r = obj[name];
        }
        return r;
    },
    /**
     * 这里使用与attr相同的获取含有"."的值，为了成功赋值，则使用重复获取"."值代码。
     * @param {Object} obj
     * @param {Object} name
     * @param {Object} v
     */
    setAttr:function(obj,name,v){
        var r,t;
        if(name==null||name==''){
            r=obj;
        }else if (name.indexOf(".") > -1) {
            t = name.split(".");
            r = obj[t[0]];
            for (var i = 1; i < t.length; i++) {
                r=r[t[i]];
            }
        } else {
           r=obj[name];
        }
        $.extend(r,v);
        return obj;
    }
};
        
 
