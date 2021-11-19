//via https://www.gatsbyjs.com/blog/2017-11-08-migrate-from-jekyll-to-gatsby/
exports.onCreateNode = ({ node, getNode, boundActionCreators }) => {
    const { createNodeField } = boundActionCreators
    if (node.internal.type === `MarkdownRemark`) {
        const { categories } = node.frontmatter
        const filename = createFilePath({ node, getNode, basePath: `pages` })
        // get the date and title from the file name
        const [, date, title] = filename.match(
            /^\/([\d]{4}-[\d]{2}-[\d]{2})-{1}(.+)\/$/
        )
        // create a new slug concatenating everything
        const slug = `/${slugify(
            categories.concat([date]).join("-"),
            "/"
        )}/${title}/`
        createNodeField({ node, name: `slug`, value: slug })
        // save the date for later use
        createNodeField({ node, name: `date`, value: date })
    }
}