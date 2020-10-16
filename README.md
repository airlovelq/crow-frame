# crow-frame

#### 介绍
基于c++ crow框架封装的后端服务框架

#### 软件架构
1. service.h service.cpp 注册服务函数
2. controller. controller.cpp 业务函数
3. database.h database.cpp 数据库操作
4. error_code.h error_code.cpp 错误码定义
5. response.h response.cpp 返回值定义
6. token.h token.cpp jwt的生成和解析
7. public_function.h public_function.cpp 公共函数定义
8. route.h CROW_ROUTE_CUSTOM宏
9. error_handler.h 异常处理template定义，及CROW_ERROR_HANDLER宏定义
10. cors.h 跨域中间件定义
11. crow_parse_template.h crow_parse.cpp 参数解析模板，意义不大，已弃用

#### 安装教程

1.  编译
2.  定义环境变量（由于目前都是用在kubernetes部署中的，用configmap来定义环境变量，程序执行过程中都会读取环境变量，如数据库连接定义等）
3.  执行

#### 使用说明

1.  如果服务函数需要使用token check，使用CROW_TOEKN_CHECK_HANDLER装饰函数
2.  尽量使用CROW_ROUTE_CUSTOM宏注册函数，其包裹的CROW_ERROR_HANDLER宏用于实现异常捕获，并规整为错误码形式，可在业务中抛出异常，但需注意尽量使用智能指针，防止抛出异常后的内存泄露


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
