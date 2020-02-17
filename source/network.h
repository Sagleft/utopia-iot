String apiQuery(String method = "getSystemInfo") {
	HTTPClient http;
	http.addHeader("Content-Type", "text/plain");

	String response = "";
	DynamicJsonDocument doc(1024);
	//StaticJsonBuffer<512> json_buffer;
	//JsonObject& jobject = json_buffer.createObject();
	//char output[128];
	
	doc["method"] = method;
	doc["token"] = API_TOKEN;
	doc["params"] = "";
	//jobject.printTo(output);

	http.begin("http://" + api_host + ":" + api_port + "/api/1.0/");
	// Send the request
	String json_query;
	serializeJson(doc, json_query);
	Serial.print(json_query);
	int httpCode = http.POST(json_query);
	// HTTP header has been send and Server response header has been handled
	Serial.printf("[HTTP] POST... code: %d\n", httpCode);
	// httpCode will be negative on error
	if(httpCode > 0) {
		if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
			response = http.getString();
			Serial.print(response);
		}
	} else {
		indicateUnknown();
		Serial.printf("[HTTP} Unable to connect\n");
	}

	http.end();
	return response;
}

bool checkClientConnection() {
	String response = apiQuery("getSystemInfo");
	if(response == "") {
		return false;
	}
	// deserialize json from utopia client
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, response);
	if(doc.containsKey("result")) {
		return true;
	} else {
		return false;
	}
}
