(function ($) {

    // Load the Handlebars content once the page is rendered
    $(window).load(function(){
    
    // Altenativley you can use the .ready below.
    // .load invokes the functionality after the DOM is rendered to the user
    // $(document).ready(function(){

        /**
         *  Reference the template.
         */

        var source = $("#handlebars_demo_page").html();
        var template = Handlebars.compile(source); 

        /**
         *  Extend functionality.
         */

        // Our JSON gives just the image URL, make it wraped in an img tag and with the media style.
        // Syntax: {{{imageRendererd image}}}

        Handlebars.registerHelper('imageRendererd', function(image) {

            // change: /sites/default/files/image.jpg
            // to:     /sites/default/files/styles/large/public/image.jpg   

            image = image.replace(/\/files\//, "\/files\/styles\/large\/public\/");        

            return "<img src='" + image + "'>'";
        });

        /**
         *  Load our data and process it into the document.
         */

        // If you wish to load in data remotely. Perhaps from the Service Views module?

        // $.get("/rest/views/rest_gallery/",function(data,status,xhr) {
        //     // Wrap the retireved data in a parent object.
        //     var dataNodes = new Object();
        //     dataNodes.nodes = data;
        //     $('.handlebars-content-target').append(template(dataNodes));
        // });

        // --------------------------

        // Or, load fixed data.

        var data = { 
            nodes: 
            [
                {"title":"Grab n drag","body":"<p>Images are linked so you can click to explore further.</p>\n","image":"http://work.allaboutken.com/sites/work.allaboutken.com/files/grab-drag-animation_0.gif","nid":"12","link":null},
                {"title":"Stuttgart Tweed Run 2014","body":"<p>Raising euros for charity, the annual Stuttgart Tweed Run offers donors a great old-fashioned time. The website conveys that experience through large visuals with the ability to read, watch, and sign-up on the same page.</p>\n","image":"http://work.allaboutken.com/sites/work.allaboutken.com/files/tweed-2014-2.jpg","nid":"19","link":"http://tweedrun.stuttgart-society.org/"}
            ]    
        }; 

        // Be sure to only use this if you load data directly from this JS file.

        $('.handlebars-content-target').append(template(data));

        // --------------------------

    });

}(jQuery));