module.exports = function(grunt) {
  grunt.initConfig({
    latex: {
      options: {
        interaction: 'nonstopmode',
        engine: 'xelatex',
      },
      files: ['flow.tex'],
    },
    watch: {
      files: ['**/*.tex'],
      tasks: ['latex']
    }
  });

  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-latex');

  grunt.registerTask('default', ['watch']);

};
