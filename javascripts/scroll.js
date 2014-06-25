// listen for scroll
$(window).scroll(
	function() {
		if ($(window).scrollTop() >= 240) {
			// fixed
			$('aside').addClass("float");
		} else {
			// relative
			$('aside').removeClass("float");
		}
	}
);