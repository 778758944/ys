var path = require("path");
module.exports = {
	mode: "production",
	entry: "./index.js",
	output: {
		path: path.resolve(__dirname, "build"),
		filename: "app.js"
	},
	module: {
		rules: [
			{
				test: /.js$/,
				exclude: /node_modules/,
				use: {
					loader: "babel-loader",
					options: {
						presets: ["env"],
					}
				}
			},
			{
				test: /.css$/,
				use: [
					{loader: "style-loader"},
					{loader: "css-loader"}, 
				]
			}
		]
	},


}

























