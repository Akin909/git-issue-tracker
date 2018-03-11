let textEl = ReasonReact.stringToElement;

let repoUrl = "https://api.github.com/repos/";

let repoOfChoice = "onivim/oni";

type repo = {
  full_name: string,
  stargazers_count: option(int),
  html_url: string,
  description: option(string),
  fork: bool,
  url: string,
  archive_url: string,
  assignees_url: string,
  blobs_url: string,
  branches_url: string,
  collaborators_url: string,
  comments_url: string,
  commits_url: string,
  compare_url: string,
  contents_url: string,
  contributors_url: string,
  downloads_url: string,
  events_url: string,
  forks_url: string,
  git_commits_url: string,
  git_url: string,
  issue_comment_url: string,
  issue_events_url: string,
  issues_url: string,
  milestones_url: string,
  notifications_url: string,
  stargazers_url: option(string),
  statuses_url: string,
  subscribers_url: string,
  subscription_url: string,
  language: string,
  forks_count: int,
  watchers_count: int,
  size: int,
  default_branch: string,
  open_issues_count: int,
  topics: option(string)
};

type issue = {
  title: string,
  number: int,
  body: string
};

let parseRepoJson = json : repo =>
  Json.Decode.{
    full_name: json |> field("full_name", string),
    stargazers_count: json |> optional(field("stargazers_count", int)),
    description: json |> optional(field("description", string)),
    fork: json |> field("fork", bool),
    url: json |> field("url", string),
    html_url: json |> field("html_url", string),
    archive_url: json |> field("archive_url", string),
    assignees_url: json |> field("assignees_url", string),
    blobs_url: json |> field("blobs_url", string),
    branches_url: json |> field("branches_url", string),
    collaborators_url: json |> field("collaborators_url", string),
    comments_url: json |> field("comments_url", string),
    commits_url: json |> field("commits_url", string),
    compare_url: json |> field("compare_url", string),
    contents_url: json |> field("contents_url", string),
    contributors_url: json |> field("contributors_url", string),
    downloads_url: json |> field("downloads_url", string),
    events_url: json |> field("events_url", string),
    forks_url: json |> field("forks_url", string),
    git_commits_url: json |> field("git_commits_url", string),
    git_url: json |> field("git_url", string),
    issue_comment_url: json |> field("issue_comment_url", string),
    issue_events_url: json |> field("issue_events_url", string),
    issues_url: json |> field("issues_url", string),
    milestones_url: json |> field("milestones_url", string),
    notifications_url: json |> field("notifications_url", string),
    stargazers_url: json |> optional(field("stargazers_url", string)),
    statuses_url: json |> field("statuses_url", string),
    subscribers_url: json |> field("subscribers_url", string),
    subscription_url: json |> field("subscription_url", string),
    language: json |> field("language", string),
    forks_count: json |> field("forks_count", int),
    watchers_count: json |> field("watchers_count", int),
    size: json |> field("size", int),
    default_branch: json |> field("default_branch", string),
    open_issues_count: json |> field("open_issues_count", int),
    topics: json |> optional(field("topics", string))
  };

let parseIssuesJson = json : array(issue) =>
  json
  |> Json.Decode.array(json =>
       Json.Decode.{
         title: json |> field("title", string),
         number: json |> field("number", int),
         body: json |> field("body", string)
       }
     );
/* let fetchIssues = (url: string, callback) =>
   Js.Promise.(
     Fetch.fetch(url)
     |> then_(Fetch.Response.json)
     |> then_(json =>
     json
     |> parseIssuesJson
     |> Array.to_list
     |> (issues => callback(issues))
     |> resolve
     )
     |> ignore
     ); */
