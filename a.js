app.post("/avatar", async (req, res) => {
    var user = res.locals.user;
    if (!user) return;
    var formidable = require('formidable');
    var form = new formidable.IncomingForm();
    form.parse(req, function (err, fields, files, next) {
        if (err) return;
        fs.rename(files.picture.path, '../static/avatar/' + user.id + ".png", (err) => {
            if (err) return;
        });
        var size = parseInt(files.picture.size);
        //获取上传的图片的大小，用作判断必须先转换成Int
        if (size > 1024 * 1024) {
            //判断图片是否过大
            fs.unlink(files.picture.path, (err) => {
                if (err) return;
            });
            //删除图片
            return;
        }
    });
    res.end();
});