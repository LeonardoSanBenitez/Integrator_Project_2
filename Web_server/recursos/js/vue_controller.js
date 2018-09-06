new Vue({
    el: '#app',
    data: {
        json: null
    },
    created: function () {
        var _this = this;

		//TODO: set time out
        $.getJSON('API_data_request.php', function (json) {
            _this.json = json;
        });
		
    },
	methods: {
		translateColor(color){
			switch(color){
				case "1": return "red"; break;
				case "2": return "blue"; break;
				case "3": return "green"; break;
				default: return "null"; 
			}
		}
	}
});