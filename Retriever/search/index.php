<html>
    <head>
        <title> Search Engine - Thiago Silva </title>
        <style type="text/css" media="all">@import "styles/body.css";</style>
        <meta charset="utf-8"></meta>
        
        <script type="text/javascript">
          $(function() {
              $('form').each(function() {
                  $(this).find('input').keypress(function(e) {
                      // Enter pressed?
                      if(e.which == 10 || e.which == 13) {
                          this.form.submit();
                      }
                  });
                  $(this).find('input[type=submit]').hide();
              });
          });
        </script> 
        
    </head>
    
    <body>
        <div id="searchbox">
              <form name="searchbar" method="get" action="">
                <div class="search-box">
                    <input type="text" value="" name="query" class="search-input" placeholder="Just Do It!!!" />
                    <!--<input type="submit" />-->
                </div>
            </form>
        </div>
    </body>
</html>
