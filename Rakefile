require 'rake/gempackagetask'
require 'rake/contrib/sshpublisher'
require 'yaml'
require 'rubyforge'
require 'ruby/lib/version'

PROJECT_NAME = "rice"
PROJECT_WEB_PATH = "/var/www/gforge-projects/rice"

task :default => :test

desc "Build Rice locally. Delete the top level Makefile to force this to run"
task :build do 
  if !File.exist?("Makefile")
    sh "bootstrap"
    sh "configure"
    sh "make"
  end
end

desc "Run unit tests" 
task :test => :build do
  cd "test" do
    ruby "test_rice.rb"
  end
end

desc "Build the documentation" 
task :doc do
  sh "make doc"
end

desc "Upload documentation to the website. Requires rubyforge gem" 
task :upload_web => [:build, :doc] do
  config = YAML.load(File.read(File.expand_path("~/.rubyforge/user-config.yml")))
  host = "#{config["username"]}@rubyforge.org"

  Rake::SshDirPublisher.new(host, PROJECT_WEB_PATH, "doc/html").upload
end

# Gemspec kept externally
eval(File.read("rice.gemspec"))
Rake::GemPackageTask.new($spec) do |pkg|
  pkg.need_zip = true
  pkg.need_tar = true
end

desc "Create a new release to Rubyforge" 
task :release => :package do
  rf = RubyForge.new
  puts "Logging into rubyforge"
  rf.login

  pkg = "pkg/#{PROJECT_NAME}-#{Rice::VERSION}"

  c = rf.userconfig

  files = [
    "#{pkg}.tgz",
    "#{pkg}.zip",
    "#{pkg}.gem"
  ]

  puts "Releasing #{PROJECT_NAME} v. #{Rice::VERSION}"
  begin
    rf.add_release $spec.rubyforge_project, PROJECT_NAME, RICE_VERSION, *files
  rescue => ex
    puts "You may not be configured with rubyforge. Please run `rubyforge config` and run this task again."
    puts "Error is #{ex.inspect}"
  end
end

