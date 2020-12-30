# webserv
## ** СОДЕРЖАНИЕ **

> В данном проекте мы пишем свой webserv, на С++/С!
(C++ && C 98 стандарт)

## ** ОСНОВНЫЕ КРИТЕРИИ **

> 1. You must write a HTTP server in C++ 98<br/>
> 2. The C++ standard must be C++ 98. Your project must compile with it.<br/>
> 3. It must be conditionnal compliant with the rfc 7230 to 7235 (http 1.1) but you need to implement only the following headers<br/>

   >>+  Accept-Charsets <br/>
   >>+  Accept-Language <br/>
   >>+  Allow<br/>
   >>+  Authorization<br/>
   >>+  Content-Language<br/>
   >>+  Content-Length<br/>
   >>+  Content-Location<br/>
   >>+  Content-Type<br/>
   >>+  Date<br/>
   >>+  Host<br/>
   >>+  Last-Modified<br/>
   >>+  Location<br/>
   >>+  Referer<br/>
   >>+  Retry-After<br/>
   >>+  Server<br/>
   >>+  Transfer-Encoding<br/>
   >>+  User-Agent<br/>
   >>+  WWW-Authenticate<br/>

> 4. You can implement all the headers if you want to:<br/>
> 5. We will consider that nginx is HTTP 1.1 compliant and may be use to compare headers and answer behaviors<br/>
> 6. It must be non blocking and use only 1 select for all the IO between the client and the server (listens includes).<br/>
> 7. Select should check read and write at the same time.<br/>
> 8. Your server should never block and client should be bounce properly if necessary<br/>
> 9. You should never do a read operation or a write operation without going through select<br/>
> 10. Checking the value of errno is strictly forbidden after a read or a write operation<br/>
> 11. A request to your server should never hang forever<br/>
> 12. You server should have default error pages if none are provided<br/>
> 13. Your program should not leak and should never crash, (even when out of memory if all the initialisation is done)<br/>
> 14. You can’t use fork for something else than CGI (like php or perl or ruby etc...)<br/>
> 15. You can include and use everything in "iostream" "string" "vector" "list" "queue" "stack" "map" "algorithm"<br/>
> 16. Your program should have a config file in argument or use a default path<br/>

  ## ** MAIN REPOS **
